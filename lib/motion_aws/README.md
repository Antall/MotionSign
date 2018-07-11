#MotionSign

## Setup

To setup the codebase you need to set a python virtual environment, activate it and load the necessary packages.

```bash
$ cd lib/motion_aws/
$ virtualenv env --python=python3
$ source env/bin/activate
$ pip install -r requirements.txt
```

## Lambda
To deploy the lambda run the following command from the projects root directory.

You also need to ensure you have the following google API credential files in the motion_aws directory:

* client_secret.json
* credentials.json

```bash
$ cd lib/motion_aws/

# zip the python file first
# ensure you have activated your python environment
$ bash deploy.sh

# upload the zipped file to the lambda function
$ cd lib/motion_aws/build/
$ aws lambda update-function-code --function-name MotionSign --zip-file fileb://MotionSign.zip

# Using SAM
$ sam local invoke "MotionSign" -e event.json
```

## API Gateway
The API Gateway is already setup to talk to the MotionSign lambda.

 The endpoint to hit is: https://tawd2jtko1.execute-api.us-east-1.amazonaws.com/prod/MotionSign

You need to set the *x-api-key: {api_key}* name/value pair in the headers.

## API Endpoints

URL: https://tawd2jtko1.execute-api.us-east-1.amazonaws.com/prod/MotionSign

#### DISPLAY
* **Method:** GET
*  **URL Params**
    * **Required:**
      `room_id=[integer]`
      `method_name=display`

#### RESERVED
* **Method:** GET
*  **URL Params**
    * **Required:**
      `room_id=[integer]`
      `reserved=[integer] # values = 1 or 0`


#### OCCUPIED
* **Method:** POST
*  **URL Params**
    * **Required:**
      `room_id=[integer]`
      `occupied=[integer] # values = 1 or 0`
