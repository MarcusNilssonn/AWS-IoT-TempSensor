#include "secrets.h"
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"

// The MQTT topics that this device should publish/subscribe
#define AWS_IOT_PUBLISH_TOPIC "Topic"
#define AWS_IOT_SUBSCRIBE_TOPIC "Topic"

WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(256);
const int tempPin = 33;     
int tempVal;  
float volts;    
float temp;   

void connectAWS() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.begin(AWS_IOT_ENDPOINT, 8883, net);

  // Create a message handler
  client.onMessage(messageHandler);

  Serial.print("Connecting to AWS IOT");

  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }

  if (!client.connected()) {
    Serial.println("AWS IoT Timeout!");
    return;
  }

  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Connected!");
}

//Function for collecting temperature
int getTemp()
{
 tempVal = analogRead(tempPin);
 volts = tempVal/1023.0;            
 temp = (volts - 0.5) * 100;  
 return temp;                       
}

//Publish to AWS
void publishMessage() {
  StaticJsonDocument<200> doc;
 
  doc["Temperature"] = getTemp();
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);  // print to client

  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
  Serial.println(jsonBuffer);
}

void messageHandler(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char *message = doc["message"];

  Serial.println(message);

}

void setup() {
  Serial.begin(115200);
  connectAWS();
}

void loop() {
  publishMessage();
  client.loop();
  delay(1000);
}
