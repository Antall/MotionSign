import logging
import boto3
import json
import time
import os

dynamo = boto3.client('dynamodb')

logger = logging.getLogger()
logger.setLevel(logging.INFO)
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
    reserved = int(params['reserved'])

    dynamo.update_item(
        TableName='MotionSign',
        Key={
            'room_id': {
                'N': str(room_id)
            }
        },
        UpdateExpression='SET reserved = :val1',
        ExpressionAttributeValues={
            ':val1': {
                'N': str(reserved)
            }
        }
    )
    return reserved

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
    return """
DATA
NOW: {}
12345678901234567890
NEXT: {}
Ben's & Antall's su
""".format(
            time.strftime("%^a %l:%M:%S %p"),
            time.strftime("%l:%M %p")
        )


def lambda_handler(event, context):
    '''Demonstrates a simple HTTP endpoint using API Gateway. You have full
    access to the request and response payload, including headers and
    status code.

    To scan a DynamoDB table, make a GET request with the TableName as a
    query string parameter. To put, update, or delete an item, make a POST,
    PUT, or DELETE request respectively, passing in the payload to the
    DynamoDB API as a JSON body.
    '''
    # print("Received event: " + json.dumps(event, indent=2))

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

