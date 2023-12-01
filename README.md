# AWS-IoT-TempSensor
This was a school project in the course IoT and cloud services which aimed to get a better understanding of working with clouds and to create an overall IoT solution, data collection from a sensor all the way to some kind of visualization of that data. In this IoT-project the temperature was measured with an ESP32 and was then sent to a database in AWS and visualized with Grafana. Outdoor temperature data was also collected with SMHI API.

## Architechture and overview
The temperature was measured and collected by a sensor and an ESP32. The data was then sent by MQTT to AWS and with a rule setting sent to a database. Also outdoor temperature from SMHI API was collected and sent to the same database using a lambda function in AWS Lambda. In the end all data could be visualized by Grafana.

***Picutre displaying the flowchart.***

![Flowchart](https://github.com/MarcusNilssonn/AWS-IoT-TempSensor/assets/113011450/f2b79b80-455d-4906-837f-b6f20f721309)

## Project description
### Hardware
This project used an ESP32 and a TMP36 temperature sensor. The ESP32 is a budget microcontroller by Espressif Systems. It was used mainy because its reduced cost and because of Wi-Fi capability which makes it suitable for IoT-apps. The TMP36 is an analog temperature sensor with three pins and gives an ouput in voltage.

The code was written in Arduino IDE where a function measured the voltage (temperature) and calculated it in Celcius. 

***Picutre displaying the sensor and the Esp32.***

![Skärmbild 2023-11-30 191155](https://github.com/MarcusNilssonn/AWS-IoT-TempSensor/assets/113011450/a2686df6-0de1-4ce2-b050-7ae6629faa4b)
### AWS IoT Core
In IoT Core a "thing" was created with the right policys and certificates. The credentials were placed in a headerfile in Arduino IDE. The project used MQTT for sending the data to a topic and a rule was set in AWS to send it further to the database.
The database was created by Timestream where all the data was sent. At first the project used DynamoDB but switched later on to Timestream because of its flexibility with Grafana.

***Picutre displaying the database.***

![Skärmbild_DB_API](https://github.com/MarcusNilssonn/AWS-IoT-TempSensor/assets/113011450/82a170b1-3523-406f-9ffe-6b57b888255f)
### API
As an addition the project also aimed to learn about APIs. So with AWS lambda, code was written in Python to collect data from SMHI open API. The weather station was set to Uppsala. After collection the data was sent to the same database in timestream as above.

In short the code uses the Boto3 library to create a Timestream client. The script makes an Http Get Request to fetch data from the weather station and loads it into a Python dictonary. The data is then transformed into a structure for Timestream and inserted to the database.

***Link to the code:*** https://github.com/MarcusNilssonn/AWS-IoT-TempSensor/blob/main/lambda_Smhi.py

***Picutre displaying weather values in to the database.***
![Skärmbild_SMHI](https://github.com/MarcusNilssonn/AWS-IoT-TempSensor/assets/113011450/e7c6c1b8-b99f-4424-9abe-fd620507952c)

### Visualization
The project used Grafana for visualization, an analytics site which can be used to visualize, analyze and make use of data. A dashboard was created with connection to the Amazon Timestream database, where SQL Query was used to retrieve values from the database.

***Picutre displaying Grafana.***
![Skärmbild_Grafana_2 0](https://github.com/MarcusNilssonn/AWS-IoT-TempSensor/assets/113011450/414e0689-ffbb-4ebc-86f6-4babaa5980b5)

### Security
The project has a variety when it comes to security where some good security work was made but with room for imporvements. The connection between hardware and AWS heavily relies on security by AWS where certificates could only be downloaded once and were together with the endpoint all placed in a secret header file and not hardcoded in the actual main code. The lambda code does not use any sensitive information but should however not have the table and tablename hardcoded since it opens up for any user to send requests to that database. The lambda code could also use a try/catch to catch any errors.
