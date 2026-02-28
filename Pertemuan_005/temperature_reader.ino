#include <Arduino.h>
#include <SimpleDHT.h>

const int pinDHT = 4;

byte temperature = 0;
byte humidity = 0;

SimpleDHT11 dht11(pinDHT);

void KelembabanSuhu()
{
    int err = SimpleDHTErrSuccess;

    if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
    {
        Serial.print("Pembacaan DHT11 gagal, err=");
        Serial.println(err);
        delay(1000);
        return;
    }

    Serial.print("Sample OK: ");
    Serial.print((int)temperature);
    Serial.print(" *C, ");
    Serial.print((int)humidity);
    Serial.println(" %"); 

    delay(1500);
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Memulai Pembacaan Simple DHT11 di ESP32...");
    delay(1000);
}

void loop()
{
    KelembabanSuhu();
}