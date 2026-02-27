// Definisikan pin warna dari RGB LED Common Cathode
const int RED_PIN = 15;
const int GREEN_PIN = 16;
const int BLUE_PIN = 17;

void setup() {
  Serial.begin(115200);
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);

  Serial.println("Praktikum 2 SOS: 3 Warna Bergantian Dimulai!");
}

void playSOS(int pinWarna, String namaWarna) {
  Serial.println("Mengirim sinyal SOS dengan warna: " + namaWarna);
  
  // 3 dits (Huruf S)
  for (int x = 0; x < 3; x++) {
    digitalWrite(pinWarna, HIGH); 
    delay(150);                  
    digitalWrite(pinWarna, LOW);  
    delay(100);                  
  }
  delay(100); // Jeda antar huruf

  // 3 dahs (Huruf O)
  for (int x = 0; x < 3; x++) {
    digitalWrite(pinWarna, HIGH); 
    delay(400);                  
    digitalWrite(pinWarna, LOW);  
    delay(100);                  
  }
  delay(100);

  // 3 dits (Huruf S)
  for (int x = 0; x < 3; x++) {
    digitalWrite(pinWarna, HIGH); 
    delay(150);                  
    digitalWrite(pinWarna, LOW);  
    delay(100);                  
  }
}

void loop() {
  // Panggil SOS Merah
  playSOS(RED_PIN, "MERAH");
  delay(5000); // Jeda 5 detik

  // Panggil SOS Hijau
  playSOS(GREEN_PIN, "HIJAU");
  delay(5000); // Jeda 5 detik

  // Panggil SOS Biru
  playSOS(BLUE_PIN, "BIRU");
  delay(5000); // Jeda 5 detik sebelum ngulang ke merah lagi
}