const int RELAY_PIN = A0;  

void setup() {
  Serial.begin(9600);
  delay(500);
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  digitalWrite(RELAY_PIN, HIGH); 
  Serial.println("Relay ON");
  delay(5000);
  digitalWrite(RELAY_PIN, LOW);
  Serial.println("Relay OFF");
  delay(5000);
}
