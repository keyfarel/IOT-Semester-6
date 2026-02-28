#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include <SimpleDHT.h>
#include <U8g2lib.h>
#include <Wire.h>

// Konfigurasi Pin
const int pinDHT = 4;
const int pinR   = 15;
const int pinG   = 16;
const int pinB   = 17;

// Inisialisasi Objek Sensor & Layar
SimpleDHT11 dht11(pinDHT);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// Konfigurasi WiFi & NTP Server
const char* ssid       = "MY_WIFI";
const char* password   = "MY_PASSWORD";
const char* ntpServer  = "pool.ntp.org";
const long  gmtOffset_sec = 7 * 3600; // UTC+7 (WIB)
const int   daylightOffset_sec = 0;

void setup() {
  Serial.begin(115200);

  // Setup Aktuator (RGB LED)
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);
  digitalWrite(pinR, LOW); digitalWrite(pinG, LOW); digitalWrite(pinB, LOW);

  u8g2.begin();

  // 1. Splash Screen
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB12_tr);
  const char* teks1 = "PRAKTIKUM";
  int x1 = (128 - u8g2.getUTF8Width(teks1)) / 2;
  u8g2.drawStr(x1, 30, teks1);

  u8g2.setFont(u8g2_font_ncenB10_tr);
  const char* teks2 = "IOT";
  int x2 = (128 - u8g2.getUTF8Width(teks2)) / 2;
  u8g2.drawStr(x2, 55, teks2);
  u8g2.sendBuffer();
  delay(2500);

  // 2. Koneksi WiFi & Animasi Loading
  WiFi.begin(ssid, password);
  int frame = 0;
  while (WiFi.status() != WL_CONNECTED) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(12, 20, "Menghubungkan...");
    
    int barWidth = (frame * 5) % 100;    
    u8g2.drawFrame(14, 40, 100, 10);     
    u8g2.drawBox(16, 42, barWidth, 6);   
    u8g2.sendBuffer();
    
    frame++;
    delay(200); 
  }

  // 3. Tampilkan IP Address
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB10_tr);
  u8g2.drawStr(25, 30, "Connected!");
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setCursor(15, 50);
  u8g2.print("IP: ");
  u8g2.print(WiFi.localIP());
  u8g2.sendBuffer();
  delay(2500); 

  // Sinkronisasi waktu NPT Server
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop() {
  // 1. Update Waktu Real-Time
  struct tm timeinfo;
  char timeStr[10];
  char dateStr[15];
  
  if(!getLocalTime(&timeinfo)){
    strcpy(timeStr, "--:--:--");
    strcpy(dateStr, "Menunggu...");
  } else {
    strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &timeinfo); 
    strftime(dateStr, sizeof(dateStr), "%d-%m-%Y", &timeinfo); 
  }

  // 2. Baca Sensor Suhu
  byte temperature = 0;
  byte humidity = 0;
  dht11.read(&temperature, &humidity, NULL);
  
  float tempC = (float)temperature;
  float tempF = (tempC * 9.0 / 5.0) + 32.0;

  // 3. Render UI Utama
  u8g2.clearBuffer();

  // Header: Tanggal
  u8g2.setFont(u8g2_font_ncenB08_tr); 
  u8g2.setCursor(2, 11);
  u8g2.print("Tgl: "); 
  u8g2.print(dateStr);
  u8g2.drawLine(0, 15, 128, 15); 

  // Body: Jam Center
  u8g2.setFont(u8g2_font_ncenB14_tr); 
  int xTime = (128 - u8g2.getUTF8Width(timeStr)) / 2;          
  u8g2.drawStr(xTime, 37, timeStr);
  u8g2.drawLine(0, 45, 128, 45); 

  // Footer: Suhu Celcius & Fahrenheit
  u8g2.setFont(u8g2_font_ncenB08_tr); 
  u8g2.setCursor(5, 59);
  u8g2.print(tempC, 1); 
  u8g2.drawCircle(35, 51, 2); 
  u8g2.drawStr(40, 59, "C");

  u8g2.drawLine(64, 48, 64, 64); 

  u8g2.setCursor(72, 59);
  u8g2.print(tempF, 1); 
  u8g2.drawCircle(105, 51, 2); 
  u8g2.drawStr(110, 59, "F");

  u8g2.sendBuffer();

  // 4. Logika Indikator Suhu (LED RGB Blink)
  int pinNyala = pinG; 
  if (tempC < 25.0) {
    pinNyala = pinG; 
  } else if (tempC >= 25.0 && tempC <= 30.0) {
    pinNyala = pinB; 
  } else {
    pinNyala = pinR; 
  }

  digitalWrite(pinNyala, HIGH);
  delay(500);
  digitalWrite(pinNyala, LOW);
  delay(500); 
}