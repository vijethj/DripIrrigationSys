#include <Wire.h>
//char ldrval;
int ldrv;
void setup() {
  Serial.begin(9600);
  // Start the I2C Bus as Slave on address 9
  Wire.begin(9); 
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
}
void receiveEvent(int bytes) {
 ldrv = Wire.read();    // read one character from the I2C
}
void loop() {

Serial.print("LDR VALUE:");
//char ldrv = Wire.read();
//String ldr= String(ldrv);
Serial.println(ldrv);
delay(2000);
}
