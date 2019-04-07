// This example uses an ESP32 Development Board
// to connect to shiftr.io.
//
// You can check on your device after a successful
// connection here: https://shiftr.io/try.
//
// by Joël Gähwiler
// https://github.com/256dpi/arduino-mqtt

#include <WiFi.h>
#include <MQTT.h>

const char ssid[] = "TISCALI-Moschettieri";
const char pass[] = "Ciao33trentini!";
const char hostname[] = "192.168.1.143";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;
unsigned long elapsedTime = 0;

void connect() {
	Serial.print("connecting to wifi...");
	while (WiFi.status() != WL_CONNECTED) {
		Serial.print(".");
		delay(1000);
	}

	Serial.print("\nWifi connected\n");
	Serial.print("\nconnecting to Mqtt broker...");

	while (!client.connect("esp32", false)) {
			Serial.print(".");
		delay(1000);
	}

	Serial.println("\nconnected to the broker!");

	client.subscribe("/time");
	// client.unsubscribe("/hello");
}


void messageReceived(String &topic, String &payload) {
	Serial.println("incoming msg " + topic + " - " + payload);

	//Serial.println("incoming msg: " + " topic : " + topic + "  payload : " + payload + " ");
}

void setup() {
	Serial.begin(115200);
	delay(1000);

	WiFi.begin(ssid, pass);

	// Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
	// You need to set the IP address directly.

	client.begin(hostname,1883, net);
	client.onMessage(messageReceived);

	connect();
}

void loop() {
	client.loop();
	delay(10);  // <- fixes some issues with WiFi stability

	if (!client.connected()) {
		connect();
	}

	// publish a message roughly every second.
	elapsedTime = (millis() - lastMillis);
	if (elapsedTime > 1000) {

		client.publish("/time", String(elapsedTime));
		lastMillis = millis();

	}
}
