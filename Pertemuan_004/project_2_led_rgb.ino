const int RED_LED = 15; 

void setup()
{
 Serial.begin(115200);
 pinMode(RED_LED, OUTPUT);
 digitalWrite(RED_LED, LOW);
 Serial.println("Contoh Program LED SOS - Mulai!");
}

void loop()
{
 // 3 dits (3 titik atau huruf S)
 Serial.println("S...");
 for (int x = 0; x < 3; x++)
 {
   digitalWrite(RED_LED, HIGH); // LED nyala (Cathode = HIGH)
   delay(150);                  // delay selama 150ms
   digitalWrite(RED_LED, LOW);  // LED mati
   delay(100);                  // delay selama 100ms
 }
 delay(100);

 // 3 dahs (3 garis atau huruf O)
 Serial.println("O...");
 for (int x = 0; x < 3; x++)
 {
   digitalWrite(RED_LED, HIGH); // LED nyala
   delay(400);                  // delay selama 400ms
   digitalWrite(RED_LED, LOW);  // LED mati
   delay(100);                  // delay selama 100ms
 }

 // 100ms delay to cause slight gap between letters
 delay(100);
 
 // 3 dits again (3 titik atau huruf S)
 Serial.println("S...");
 for (int x = 0; x < 3; x++)
 {
   digitalWrite(RED_LED, HIGH); // LED nyala
   delay(150);                  // delay selama 150ms
   digitalWrite(RED_LED, LOW);  // LED mati
   delay(100);                  // delay selama 100ms
 }

 Serial.println("Jeda 5 detik...");
 // wait 5 seconds before repeating the SOS signal
 delay(5000);
}