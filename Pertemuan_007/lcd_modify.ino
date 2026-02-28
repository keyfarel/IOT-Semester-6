#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void setup() {
  Serial.begin(115200);
  u8g2.begin();  
}

void scrollTextOLED(int y, String message, int delayTime) {
  u8g2.setFont(u8g2_font_ncenB12_tr); 
  int textWidth = u8g2.getUTF8Width(message.c_str());
  
  for (int x = 128; x > -textWidth; x--) {
    u8g2.clearBuffer();
  
    // Bingkai luar dengan sudut melengkung
    u8g2.drawRFrame(0, 0, 128, 64, 5);

    // Menampilkan Nama Rata Tengah
    u8g2.setFont(u8g2_font_ncenB10_tr);
    const char* nama = "Key Firdausi";
    int xNama = (128 - u8g2.getUTF8Width(nama)) / 2;
    u8g2.drawStr(xNama, 25, nama); 
    
    // Garis pembatas di bawah nama
    u8g2.drawLine(10, 32, 118, 32);

    // Teks Berjalan 
    u8g2.setFont(u8g2_font_ncenB12_tr);
    u8g2.drawStr(x, y, message.c_str());
    
    u8g2.sendBuffer();
    delay(delayTime); 
  }
}

void loop() {
  scrollTextOLED(53, "Praktikum IoT - D4 Teknik Informatika", 10);
}