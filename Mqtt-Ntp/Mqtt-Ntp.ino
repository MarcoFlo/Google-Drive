#include <NTPClient.h>
#include <WiFi.h>
#include <MQTT.h>
#include "./credentials.h"

//const char ssid[] = "modemMarco";
//const char pass[] = "password";
//const char hostname[] = "192.168.1.3";


WiFiClient net;
MQTTClient clientMQTT;
WiFiUDP ntpUDP;
//GMT +1 = 3600
//GMT +1 = 7200 per ora legale

NTPClient timeClient(ntpUDP, "pool.ntp.org", 7200, 60000);

unsigned long lastMillis = 0;
unsigned long elapsedTime = 0;

void connectMQTT()
{
  Serial.print("\nconnecting to Mqtt broker...");

  while (!clientMQTT.connect("esp32", false)) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected to the broker!");

  clientMQTT.subscribe("/time", 2);
  // clientMQTT.unsubscribe("/hello");

}
void connectWifi() {
  Serial.print("connecting to wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nWifi connected\n");



}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming msg: topic : " + topic + "\tpayload : " + payload );
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(ssid, pass);
  connectWifi();
  
  clientMQTT.begin(hostname, 1883, net);
  clientMQTT.onMessage(messageReceived);
  connectMQTT();

  timeClient.begin();
}

void loop() {
  clientMQTT.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!clientMQTT.connected()) {
    connectMQTT();
  }

  // publish a message roughly every second.
  elapsedTime = (millis() - lastMillis);
  if (elapsedTime > 1000) {

    clientMQTT.publish("/time", String(elapsedTime), true, 2);
    lastMillis = millis();

    //force update
    while (!timeClient.update()) {
      timeClient.forceUpdate();
    }

    Serial.println("ntp time " + String(timeClient.getFormattedTime()));
  }
}
