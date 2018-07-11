#MotionSign

## Lambda
To deploy the lambda run the following command from the projects root directory.

```bash
$ cd lib/motion_aws/

# zip the python file first
$ bash deploy.sh

# upload the zipped file to the lambda function
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
