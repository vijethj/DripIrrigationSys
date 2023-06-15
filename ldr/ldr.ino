int ldr=A0;
int value=0;
void setup() {
Serial.begin(9600);
}

void loop() {
value=analogRead(ldr);
Serial.println("LDR value is :");
Serial.println(value);
delay(3000);
}
