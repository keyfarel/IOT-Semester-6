#include <Arduino.h>
#include <SimpleDHT.h>

const int pinDHT = 4;
const int pinR = 15;
const int pinG = 16;
const int pinB = 17;

SimpleDHT11 dht11(pinDHT);

void setup() {
    Serial.begin(115200);
    pinMode(pinR, OUTPUT);
    pinMode(pinG, OUTPUT);
    pinMode(pinB, OUTPUT);
    digitalWrite(pinR, LOW);
    digitalWrite(pinG, LOW);
    digitalWrite(pinB, LOW);
    Serial.println("[SYSTEM] Memulai Pemantauan Suhu Kota...");
    delay(2000);
}

void loop() {
    byte temperature = 0;
    byte humidity = 0;
    int err = SimpleDHTErrSuccess;

    // Baca data dari DHT11
    if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
        Serial.print("[ERROR] Gagal membaca sensor DHT11, err=");
        Serial.println(err);
        delay(2000);
        return;
    }

    // Konversi Suhu
    float tempC = (float)temperature;
    float tempK = tempC + 273.15;
    float tempR = tempC * 0.8;

    String kategori = "";
    String warnaLED = "";

    // Logika Indikator LED RGB Kota
    if (tempC < 25) {
        kategori = "DINGIN";
        warnaLED = "HIJAU";
        digitalWrite(pinR, LOW);
        digitalWrite(pinG, HIGH); // Hijau Nyala
        digitalWrite(pinB, LOW);
    } 
    else if (tempC >= 25 && tempC <= 30) {
        kategori = "NORMAL";
        warnaLED = "BIRU";
        digitalWrite(pinR, LOW);
        digitalWrite(pinG, LOW);
        digitalWrite(pinB, HIGH); // Biru Nyala
    } 
    else { // tempC > 30
        kategori = "PANAS";
        warnaLED = "MERAH";
        digitalWrite(pinR, HIGH); // Merah 
        digitalWrite(pinG, LOW);
        digitalWrite(pinB, LOW);
    }
    
    unsigned long waktu = millis(); 
    Serial.print("[");
    Serial.print(waktu);
    Serial.print("] Temp: ");
    Serial.print(tempC); Serial.print(" C, ");
    Serial.print(tempK); Serial.print(" K, ");
    Serial.print(tempR); Serial.print(" R | Hum: ");
    Serial.print((int)humidity); Serial.print("% | Status: ");
    Serial.print(kategori);
    Serial.print(" (LED: ");
    Serial.print(warnaLED);
    Serial.println(")");
    delay(2000); 
}