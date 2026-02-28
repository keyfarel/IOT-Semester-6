#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

8X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  Serial.begin(115200);
  u8g2.begin();  
  u8g2.setFont(u8g2_font_ncenB12_tr);
}

void scrollTextOLED(int y, String message, int delayTime) {
    int textWidth = u8g2.getUTF8Width(message.c_str());
  
  for (int x = 128; x > -textWidth; x--) {
    u8g2.clearBuffer();
    u8g2.drawStr(25, 25, "Polinema"); 
    u8g2.drawStr(x, y, message.c_str());
    
    u8g2.sendBuffer();
    delay(delayTime); 
  }
}

void loop() {
  scrollTextOLED(55, "Kelas IoT.", 10);
}