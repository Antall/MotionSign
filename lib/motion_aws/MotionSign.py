
import boto3
import json

print('Loading function')
dynamo = boto3.client('dynamodb')


def respond(err, res=None):
    return {
        'statusCode': '400' if err else '200',
        'body': err.message if err else json.dumps(res),
        'headers': {
            'Content-Type': 'application/json',
        },
    }


def __get_methods(dynamo, params):
    room_id = params.get('room_id')
    method_name = params.get('method_name')

    methods = {
        'reserved': lambda dynamo, room_id: __reserved(dynamo, room_id),
        'display': lambda dynamo, room_id: __display(dynamo, room_id)
    }

    if method_name in methods and room_id:
        return respond(None, methods[method_name](dynamo, room_id))
    else:
        if room_id == None:
            return respond(ValueError('Room ID is missing'))
        else:
            return respond(ValueError('Unsupported method "{}"'.format(method_name)))


def __reserved(dynamo, room_id):
    room_entry = dynamo.get_item(
            TableName='MotionSign',
            Key={
                'room_id': { 'N': room_id }
            })
    print(room_entry)
    return room_entry


def __display(dynamo, room_id):
    room_entry = dynamo.get_item(
            TableName='MotionSign',
            Key={
                'room_id': { 'N': room_id }
            })
    print(room_entry)
    return room_entry


def lambda_handler(event, context):
    '''Demonstrates a simple HTTP endpoint using API Gateway. You have full
    access to the request and response payload, including headers and
    status code.

    To scan a DynamoDB table, make a GET request with the TableName as a
    query string parameter. To put, update, or delete an item, make a POST,
    PUT, or DELETE request respectively, passing in the payload to the
    DynamoDB API as a JSON body.
    '''
    #print("Received event: " + json.dumps(event, indent=2))

    operations = {
        'DELETE': lambda dynamo, x: dynamo.delete_item(**x),
        'GET': lambda dynamo, x: __get_methods(dynamo, x),
        'POST': lambda dynamo, x: dynamo.put_item(**x),
        'PUT': lambda dynamo, x: dynamo.update_item(**x),
    }

    operation = event['httpMethod']
    if operation in operations:
        payload = event['queryStringParameters'] if operation == 'GET' else json.loads(event['body'])
        return operations[operation](dynamo, payload)
    else:
        return respond(ValueError('Unsupported method "{}"'.format(operation)))

