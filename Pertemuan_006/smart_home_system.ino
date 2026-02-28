#include <Arduino.h>
#include <SimpleDHT.h>

const int pinDHT = 4;
const int pinLDR = 34;
const int pinR   = 15;
const int pinG   = 16;
const int pinB   = 17;

SimpleDHT11 dht11(pinDHT);

const int batasCahaya = 1500;   
const float batasDingin = 25.0; 
const float batasPanas = 30.0;  

void setup() {
    Serial.begin(115200);
    
    pinMode(pinR, OUTPUT);
    pinMode(pinG, OUTPUT);
    pinMode(pinB, OUTPUT);
    
    digitalWrite(pinR, LOW);
    digitalWrite(pinG, LOW);
    digitalWrite(pinB, LOW);
    
    Serial.println("[SYSTEM] Sistem Smart Home Aktif...");
    delay(2000);
}

void loop() {
    int nilaiLDR = analogRead(pinLDR);
    
    byte temperature = 0;
    byte humidity = 0;
    dht11.read(&temperature, &humidity, NULL);
    float tempC = (float)temperature;

    unsigned long waktu = millis();
    Serial.print("[");
    Serial.print(waktu);
    Serial.print("] LDR: ");
    Serial.print(nilaiLDR);
    Serial.print(" | Temp: ");
    Serial.print(tempC);
    Serial.print(" C | Status: ");

    if (nilaiLDR < batasCahaya && tempC < batasDingin) {
        Serial.println("REDUP & DINGIN (LED BIRU KEDIP)");
        digitalWrite(pinR, LOW);
        digitalWrite(pinG, LOW);
        
        for(int i = 0; i < 3; i++) {
            digitalWrite(pinB, HIGH);
            delay(300);
            digitalWrite(pinB, LOW);
            delay(300);
        }
    }
    else if (nilaiLDR >= batasCahaya && tempC > batasPanas) {
        Serial.println("TERANG & PANAS (LED MERAH NYALA)");
        digitalWrite(pinR, HIGH);
        digitalWrite(pinG, LOW);
        digitalWrite(pinB, LOW);
        delay(1800); 
    }
    else {
        Serial.println("NORMAL (LED MATI)");
        digitalWrite(pinR, LOW);
        digitalWrite(pinG, LOW);
        digitalWrite(pinB, LOW);
        delay(1800); 
    }
}