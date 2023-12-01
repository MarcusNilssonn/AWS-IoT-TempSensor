# AWS-IoT-TempSensor
This was a school project in the course IoT and cloud services which aimed to get a better understanding of working with clouds and to create an overall IoT solution, data collection from a sensor all the way to some kind of visualization of that data. In this IoT-project the temperature was measured with an Esp32 and was then sent to a database in AWS and visualized with Grafana. Outdoor temperature data was also collected with SMHI API.

## Architechture and overview
The temperature was measured and collected by a sensor and an Esp32. The data was then sent by MQTT to AWS and with a rule setting sent to a database. Also outdoor temperature from SMHI API was collected and sent to the same database using a lambda function in AWS Lambda. In the end all data could be visualized by Grafana.

***Picutre displaying the flowchart.***

![Flowchart](https://github.com/MarcusNilssonn/AWS-IoT-TempSensor/assets/113011450/f2b79b80-455d-4906-837f-b6f20f721309)

## Project description
### Hardware
This project used an Esp32 and a tmp36 temperature sensor. The code was written in Arduino IDE.

***Picutre displaying the sensor and the Esp32.***

![Skärmbild 2023-11-30 191155](https://github.com/MarcusNilssonn/AWS-IoT-TempSensor/assets/113011450/a2686df6-0de1-4ce2-b050-7ae6629faa4b)
### AWS IoT Core
In IoT Core a "thing" was created with the right policys and certificates. The credentials were placed in a headerfile in Arduino IDE. The project used MQTT for sending the data to a topic and a rule was set in AWS to send it further to the database.
The database was created by Timestream because of its flexibility with Grafana.

***Picutre displaying the database.***

![Skärmbild_DB_API](https://github.com/MarcusNilssonn/AWS-IoT-TempSensor/assets/113011450/82a170b1-3523-406f-9ffe-6b57b888255f)
### API
As an addition the project also aimed to learn about APIs. So with AWS lambda, code was written in Python to collect data from SMHI open API. The weather station was set to Uppsala. After collection the data was sent to the same database in timestream as above.
### Visualization
The project used Grafana for visualization where SQL query was used to retrieve values from the database.

***Picutre displaying Grafana.***

![Skärmbild_Grafana](https://github.com/MarcusNilssonn/AWS-IoT-TempSensor/assets/113011450/4750ce7c-22f1-4359-9ce3-bc944a54d163)

