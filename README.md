# AWS-IoT-TempSensor
This project was an IoT-project where the temperature was measured with a esp32 and the was sent to a database in AWS and visualized with Grafana. Outdoor temperature data was also collected with SMHI API.

## Architechture and overview
The temperature was measured and collected by a sensor and a esp32. The data was then sent by MQTT to AWS and with a rule setting sent to a database. Also outdoor temperature from SMHI API was collected and sent to the same database using a lambda function in AWS Lambda. In the ens all data could be visualized by Grafana.

***Picutre displaying the flowchart***
![Flowchart](https://github.com/MarcusNilssonn/AWS-IoT-TempSensor/assets/113011450/b6bfaff4-1657-4576-ac9f-5b040e421af9)

## Project description
### Hardware
This project used an Esp32 and a tmp36 temperature sensor. The code was written in Arduino IDE.
### IoT Core
In IoT Core a "thing" was created with the right policys and certificates. The credentials were placed in a headerfile in Arduino IDE. The project used MQTT for sending the data and a rule was set in AWS to send it further to the database.
The database was created by Timestream because of its flexibility with Grafana.
***Picutre displaying the database***
![Skärmbild_DB_API](https://github.com/MarcusNilssonn/AWS-IoT-TempSensor/assets/113011450/82a170b1-3523-406f-9ffe-6b57b888255f)
### API
As an addition the project also aimed to learn about APIs. So with AWS lambda code was written in Python to collect data from SMHI open API. The data was also sent to the same database as above.
### Visualization
The project used Grafana for visualization.
***Picutre displaying the Grafana***
![Skärmbild_Grafana](https://github.com/MarcusNilssonn/AWS-IoT-TempSensor/assets/113011450/4750ce7c-22f1-4359-9ce3-bc944a54d163)

