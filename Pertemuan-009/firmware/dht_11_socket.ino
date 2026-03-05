/**
 * DHT11 Sensor TCP Client for ESP32
 * 
 * This firmware reads temperature and humidity data from a DHT11 sensor
 * and sends it to a remote TCP server over a WiFi connection.
 */

#include <WiFi.h>
#include "DHT.h"

// DHT11 Pin Configuration
#define DHTPIN 4       
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// WiFi Credentials Configuration
const char *ssid = "DINATA"; 
const char *password = "Perditampan13";

// Remote Server Configuration
const char *host = "khzxx-103-184-18-52.a.free.pinggy.link"; 
const uint16_t port = 45947;

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  Serial.printf("\nConnecting to WiFi: %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected successfully!");
}

void loop() {
  // Read humidity and temperature from DHT11
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Validate sensor readings
  if (isnan(h) || isnan(t)) {
    Serial.println("Error: Failed to read from DHT11 sensor. Check wiring.");
    delay(2000);
    return;
  }

  WiFiClient client;
  Serial.printf("\n[Connecting to %s:%d ... ", host, port);
  
  if (client.connect(host, port)) {
    Serial.println("Connected!]");

    // Format the payload data
    String payload = "Suhu: " + String(t) + "C, Lembap: " + String(h) + "%";
    Serial.println("[Sending Data] " + payload);
    client.println(payload);

    // Wait for acknowledgment from the server
    String response = client.readStringUntil('\n');
    Serial.println("[Server Response] " + response);
    
    client.stop();
  } else {
    Serial.println("Connection Failed!]");
  }
  
  // Wait before sending the next reading
  delay(5000); 
}