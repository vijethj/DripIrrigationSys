#define rainfall A2
#define buzzer 5
int rainvalue;
int set=10;
void setup() {
  Serial.begin(9600);
 // pinMode(buzzer,OUTPUT);
  pinMode(rainfall,INPUT);
  }
void loop() {

 rainvalue = analogRead(rainfall);
 Serial.println(rainvalue);
 rainpercent = map(value,0,1023,100,0);
 Serial.println(rainpercent);
 delay(5000);
}
