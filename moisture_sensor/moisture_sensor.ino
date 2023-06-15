int sensorPin = A1; 
int sensorValue;  
int moistpercentage;
void setup() {
 Serial.begin(9600);
 pinMode(sensorPin, INPUT);
}

void loop() {

 sensorValue = analogRead(sensorPin); 
 Serial.println("Analog Value : ");
 Serial.println(sensorValue);
 moistpercentage = map(sensorValue,0,1023,100,0);
 Serial.println(moistpercentage);
 delay(3000); 
}
