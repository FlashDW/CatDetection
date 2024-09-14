#include <WiFi.h>
#include <PubSubClient.h>

// Replace with your Wi-Fi and broker details
const char* ssid = "RobloxFTW";
const char* password = "hardball";
const char* mqtt_server = "192.168.1.157";  // Replace with the IP address of your PC where Mosquitto is running

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  client.setServer(mqtt_server, 1883);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32-CAM")) {
      Serial.println("Connected to MQTT Broker");
    } else {
      Serial.print("Failed to connect. State: ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  // Example publish to confirm connection
  client.publish("home/camera/cat_detection", "Test message");
}

void loop() {
  client.loop();
  // Add your image publishing code here
}
