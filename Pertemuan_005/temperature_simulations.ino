#include <Arduino.h>
#include <SimpleDHT.h>

// Definisi Pin Sensor & LED
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
    
    Serial.println("[SYSTEM] Memulai Pemantauan Suhu Kota (Mode Demo Bertahap)...");
    delay(2000);
}

void loop() {
    byte temperature = 0;
    byte humidity = 0;
    
    dht11.read(&temperature, &humidity, NULL);

    // Manipulasi naik turun bertahap
    static float tempC = 21.0; // Dimulai dari suhu dingin
    static float step = 1.5;   // Nilai kenaikan/penurunan suhu per siklus

    // Tambahkan suhu dengan step
    tempC += step;

    // Kalau suhu sudah mecapai batas atas (Panas), ubah arah step jadi minus (turun)
    if (tempC >= 33.0) {
        step = -1.5; 
    } 
    // Kalau suhu sudah mencapai batas bawah (Dingin), ubah arah step jadi plus (naik)
    else if (tempC <= 21.0) {
        step = 1.5;  
    }

    // Konversi Suhu
    float tempK = tempC + 273.15;
    float tempR = tempC * 0.8;

    String kategori = "";
    String warnaLED = "";

    // Logika Indikator LED RGB Kota
    if (tempC < 25.0) {
        kategori = "DINGIN";
        warnaLED = "HIJAU";
        digitalWrite(pinR, LOW);
        digitalWrite(pinG, HIGH); // Hijau Nyala
        digitalWrite(pinB, LOW);
    } 
    else if (tempC >= 25.0 && tempC <= 30.0) {
        kategori = "NORMAL";
        warnaLED = "BIRU";
        digitalWrite(pinR, LOW);
        digitalWrite(pinG, LOW);
        digitalWrite(pinB, HIGH); // Biru Nyala
    } 
    else { // tempC > 30.0
        kategori = "PANAS";
        warnaLED = "MERAH";
        digitalWrite(pinR, HIGH); // Merah Nyala
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
    
    // Jeda 1,5 detik biar video demonya dinamis dan nggak nunggu lama
    delay(1500); 
}