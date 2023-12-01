import boto3 #Lib for interacting with AWS services.
import json #Lib for handling JSON data.
import urllib3 #Lib for making HTTP req.

#Initilaze a timstream client.
timestreamWrite = boto3.client('timestream-write')

def lambda_handler(event, context):
   
    http = urllib3.PoolManager()
    #Weather data from Uppsala Station
    res = http.request('GET', 'https://opendata-download-metobs.smhi.se/api/version/latest/parameter/1/station/97510/period/latest-hour/data.json')
    
    data = json.loads(res.data.decode('utf-8')) 

    #Get the data from the API response.  
    records = [
        {
            'Dimensions': [
                {'Name': 'device_id', 
                'Value': data["station"]["name"]}
                   
            ],
            'MeasureName': 'Temperature outdoor',
            'MeasureValue': str(data["value"][0]["value"]), 
            'Time': str(data["value"][0]["date"])  
        }
           
    ]
    
    # Send records to Timestream table
    response = timestreamWrite.write_records(DatabaseName='DatabaseName', TableName='tableName', Records=records)
    
    return 'Data successfully inserted into database'
