const int pinLDR = 34; 

void setup() {
  Serial.begin(115200);
  Serial.println("Contoh Penggunaan Sensor LDR");
  delay(3000);
}

void loop() {
  int nilaiLDR = analogRead(pinLDR);
  Serial.print("Nilai Sensor: ");
  Serial.println(nilaiLDR);
  delay(1000); 
}