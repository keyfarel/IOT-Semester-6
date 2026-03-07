/**
 * Smart Village Client Firmware
 *
 * This firmware connects an ESP32 to a designated Wi-Fi network and a
 * remote TCP server. It reads temperature and humidity from a DHT11 sensor 
 * and light intensity from an LDR. It formats this data into a payload, 
 * sends it to the server, and processes incoming commands to control an LED.
 */

#include <WiFi.h>
#include "DHT.h"

// Pin Definitions
#define DHTPIN 4
#define DHTTYPE DHT11
#define LDR_PIN 34
#define LED_PIN 2

// Global Instances
DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;

// Network Credentials
const char *ssid = "DINATA"; 
const char *password = "Perditampan13";

// Server Configuration
const char *host = "jlliv-103-184-18-52.a.free.pinggy.link"; 
const uint16_t port = 35393;            

/**
 * Custom Logging Function
 * Digunakan untuk menstandarkan output Serial Monitor
 */
void logOutput(const char* level, const String& message) {
  Serial.printf("[%s] %s\n", level, message.c_str());
}

/**
 * Initializes and connects to the specified Wi-Fi network.
 * Blocks execution until a connection is established.
 */
void connect_wifi() {
  logOutput("INFO", "Menghubungkan ke Wi-Fi: " + String(ssid));
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    logOutput("INFO", "Menunggu koneksi Wi-Fi...");
  }
  
  logOutput("INFO", "Wi-Fi berhasil terhubung! IP: " + WiFi.localIP().toString());
}

/**
 * Connects to the designated TCP server.
 * Retries every 2 seconds if the connection fails.
 */
void connect_server() {
  while (!client.connected()) {
    logOutput("INFO", "Mencoba terhubung ke Server: " + String(host));
    if (client.connect(host, port)) {
      logOutput("INFO", "Berhasil terhubung ke Server Pinggy!");
    } else {
      logOutput("WARN", "Koneksi ke server gagal, mencoba lagi dalam 2 detik...");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(100); 
  logOutput("INFO", "Memulai Firmware Smart Village");
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  dht.begin();
  connect_wifi();
}

void loop() {
  if (!client.connected()) {
    logOutput("WARN", "Koneksi terputus dari server.");
    connect_server();
  }

  float t = dht.readTemperature();
  float h = dht.readHumidity();
  int ldrValue = analogRead(LDR_PIN);
  
  String kondisiCahaya = (ldrValue > 2000) ? "Siang" : "Malam"; 

  if (isnan(h) || isnan(t)) {
    logOutput("ERROR", "Gagal membaca data dari sensor DHT11!");
    delay(2000);
    return;
  }

  String payload = "Suhu: " + String(t) + "C, Lembap: " + String(h) + "%, Cahaya: " + kondisiCahaya + " (" + String(ldrValue) + ")";
  
  logOutput("INFO", "Payload terformat: " + payload);
  client.println(payload);

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      logOutput("ERROR", "Waktu tunggu respons server habis (Timeout)!");
      client.stop();
      return;
    }
  }

  String response = client.readStringUntil('\n');
  response.trim();
  logOutput("INFO", "Menerima respons: " + response);

  if (response.equalsIgnoreCase("led-on")) {
    digitalWrite(LED_PIN, HIGH);
    logOutput("INFO", "Aksi aktuator: Lampu Jalan DINYALAKAN");
  } else if (response.equalsIgnoreCase("led-off")) {
    digitalWrite(LED_PIN, LOW);
    logOutput("INFO", "Aksi aktuator: Lampu Jalan DIMATIKAN");
  }

  delay(5000);
}