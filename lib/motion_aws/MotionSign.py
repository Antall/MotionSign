from __future__ import print_function
import logging
import boto3
import json
import time
import os
import httplib2
from apiclient import discovery
import oauth2client
from oauth2client import client
from oauth2client import tools
import pytz
import datetime
import shutil
import iso8601


dynamo = boto3.client('dynamodb')

logger = logging.getLogger()
logger.setLevel(logging.INFO)

# setup timezones stuff
eastern = pytz.timezone('US/Eastern')
os.environ["TZ"]="US/Eastern"
time.tzset()


def respond(msg=""):
    return msg


def __get_methods(dynamo, params):
    method_name = params.get('method_name')

    methods = {
        'reserved': lambda dynamo, params: __reserved(dynamo, params),
        'display': lambda dynamo, params: __display(dynamo, params)
    }

    if method_name not in methods:
        method_name = 'reserved'

    return respond(methods[method_name](dynamo, params))

"""
Method to display reservation details for the room

- parse parameter list for room_id
- parse parameter list for occupied flag
- update occupied flag
"""
def __occupied(dynamo, params):
    room_id = params['room_id']
    occupied = int(params['occupied'])

    dynamo.update_item(
        TableName='MotionSign',
        Key={
            'room_id': {
                'N': str(room_id)
            }
        },
        UpdateExpression='SET occupied = :val1',
        ExpressionAttributeValues={
            ':val1': {
                'N': str(occupied)
            }
        }
    )
    return "OCCUPIED" if occupied == 1 else "EMPTY"



"""
Method to display reservation details for the room

- parse parameter list for room_id
- parse parameter list for reserved flag
- update reserved flag
"""
def __reserved(dynamo, params):
    room_id = params['room_id']
    occupied = int(params['occupied'])

    dynamo.update_item(
        TableName='MotionSign',
        Key={
            'room_id': {
                'N': str(room_id)
            }
        },
        UpdateExpression='SET occupied = :val1',
        ExpressionAttributeValues={
            ':val1': {
                'N': str(occupied)
            }
        }
    )
    reserved = 1 - occupied
    return reserved

def get_credentials():
    """Gets valid user credentials from storage.

    If nothing has been stored, or if the stored credentials are invalid,
    the OAuth2 flow is completed to obtain the new credentials.

    Returns:
        Credentials, the obtained credential.
    """
    # credentials = GoogleCredentials.get_application_default()
    credential_path = '/tmp/credentials.json'
    store = oauth2client.file.Storage(credential_path)
    credentials = store.get()
    return credentials

"""
Method to display reservation details for the room

- parse parameter list for room_id
- fetch room details
"""
def __display(dynamo, params):
    room_id = params['room_id']
    room_entry = dynamo.get_item(
            TableName='MotionSign',
            Key={
                'room_id': { 'N': room_id }
            })

    calendar_id = room_entry['Item'].get('calendar_id').get('S')

    credentials = get_credentials()
    http = credentials.authorize(httplib2.Http())
    service = discovery.build('calendar', 'v3', http=http, cache_discovery=False)

    now = datetime.datetime.utcnow().isoformat() + 'Z' # 'Z' indicates UTC time
    eventsResult = service.events().list(
        calendarId=calendar_id,
        timeMin=now,
        maxResults=2,
        singleEvents=True,
        orderBy='startTime'
    ).execute()
    events = eventsResult.get('items', [])

    return __build_str(events)

def __build_event_str(event):
    start = event['start'].get('dateTime', event['start'].get('date'))
    end = event['end'].get('dateTime', event['end'].get('date'))

    event_start = iso8601.parse_date(start).astimezone(eastern)
    event_end = iso8601.parse_date(end).astimezone(eastern)
    current_datetime = datetime.datetime.now(eastern)

    event_summary = event['summary'][:20]

    if event_start < current_datetime < event_end:
        return """
NOW: {}
{}""".format(current_datetime.strftime("%^a %l:%M:%S %p"),event_summary)
    else:
        return """
NEXT:   {}
{}""".format(event_start.strftime("%^a %l:%M %p"), event_summary)


def __build_str(events):
    event_strings = [__build_event_str(event) for event in events]

    return """
DATA{}
""".format(''.join(event_strings))




def lambda_handler(event, context):
    '''Demonstrates a simple HTTP endpoint using API Gateway. You have full
    access to the request and response payload, including headers and
    status code.

    To scan a DynamoDB table, make a GET request with the TableName as a
    query string parameter. To put, update, or delete an item, make a POST,
    PUT, or DELETE request respectively, passing in the payload to the
    DynamoDB API as a JSON body.
    '''

    # copy the credential file into tmp directory
    # we can read the file from there, else we run into
    # permission issues
    credential_path = os.path.join(os.environ['LAMBDA_TASK_ROOT'], 'credentials.json')
    shutil.copy(credential_path, "/tmp/credentials.json")


    operations = {
        'GET': lambda dynamo, x: __get_methods(dynamo, x),
        'POST': lambda dynamo, x: respond(__occupied(dynamo, x))
    }

    operation = event['context']['http-method']
    payload = event['params']['querystring']

    if operation in operations:
        return operations[operation](dynamo, payload)
    else:
        return respond(ValueError('Unsupported method "{}"'.format(operation)))

