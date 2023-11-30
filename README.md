# AWS-IoT-TempSensor
This project was an IoT-project where the temperature was measured with a esp32 and the was sent to a database in AWS and visualized with Grafana. Outdoor temperature data was also collected with SMHI API.

## Architechture and overview
The temperature was measured and collected by a sensor and a esp32. The data was then sent by MQTT to AWS and with a rule setting sent to a database. Also outdoor temperature from SMHI API was collected and sent to the same database using a lambda function in AWS Lambda. In the ens all data could be visualized by Grafana.

***Picutre displaying the flowchart***

![Flowchart](https://github.com/MarcusNilssonn/AWS-IoT-TempSensor/assets/113011450/b6bfaff4-1657-4576-ac9f-5b040e421af9)

## Project description
####Hardware####
This project used an Esp32 and a tmp36 temperature sensor.

