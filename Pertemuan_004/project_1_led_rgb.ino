const int pinR = 15;
const int pinG = 16;
const int pinB = 17;

void setup() {
  Serial.begin(115200);
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);
}

void ledRgb(){
  // Nyalakan Merah saja
  digitalWrite(pinR, HIGH);
  digitalWrite(pinG, LOW);
  digitalWrite(pinB, LOW);
  Serial.println("LED Merah nyala");
  delay(1000);

  // Nyalakan Hijau saja
  digitalWrite(pinR, LOW);
  digitalWrite(pinG, HIGH);
  digitalWrite(pinB, LOW);
  Serial.println("LED Hijau nyala");
  delay(1000);

  // Nyalakan Biru saja
  digitalWrite(pinR, LOW);
  digitalWrite(pinG, LOW);
  digitalWrite(pinB, HIGH);
  Serial.println("LED Biru nyala");
  delay(1000);
}

void loop() {
  ledRgb();
}