#include <Wire.h>

void setup() {
  Wire.begin(); // Mengaktifkan jalur I2C ESP32 (SDA: 21, SCL: 22)
  Serial.begin(115200);
  Serial.println("\nI2C Scanner Memulai...");
}

void loop() {
  byte error, address;
  int nDevices;
  
  Serial.println("Scanning...");
  nDevices = 0;
  
  // Melakukan perulangan untuk mengecek alamat 1 sampai 127
  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    
    if (error == 0) {
      Serial.print("I2C device ditemukan pada alamat 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      nDevices++;
    }
    else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }    
  }
  
  if (nDevices == 0) {
    Serial.println("Tidak ada device I2C yang ditemukan\n");
  }
  else {
    Serial.println("Selesai\n");
  }
  
  delay(3000); // Ulangi scan setiap 3 detik         
}