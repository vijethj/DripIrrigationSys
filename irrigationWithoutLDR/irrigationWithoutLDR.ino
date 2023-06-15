//PUMP
const int RELAY_PIN = A0;

/*
//LDR
int ldr=A0;
int ldrv=0;
int ldrpercent;
int ldrthreshold=500;
*/

//LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2); 

//Moisture Sensor
int sensorPin = A1; 
int sensorValue;  
int moistpercent;
int moistthresh= 500;

//Raindrop Sensor
#define rainfall A2
//#define buzzer 5
int rainvalue;
int rainpercent;
int rainthresh=700;
//int set=10; (Set value for when using a buzzer)

//DHT
#include <dht.h>
#define dht_apin A3
dht DHT;
int dhttempthresh= 30;
int dhthumidthresh= 80;
int dhthumidthresh2= 40;
int dhttemp;
int dhthumid;

void setup() {
  Serial.begin(9600);
  delay(500);
  pinMode(RELAY_PIN, OUTPUT); //PUMP
  pinMode(2, INPUT); //Touch Sensor
  pinMode(rainfall,INPUT); //Raindrop Sensor
  pinMode(sensorPin, INPUT); //Moisture Sensor
  lcd.begin(); //LCD
  lcd.backlight(); //LCD
  delay(1000);
}

void loop(){
  
  digitalWrite(RELAY_PIN, HIGH);
  //Moisture
  sensorValue = analogRead(sensorPin); 
  Serial.print("Soil Moisture Analog Value : ");
  Serial.println(sensorValue);
  moistpercent = map(sensorValue,0,1023,100,0);
  Serial.print("Soil Moisture Level Percentage: ");
  Serial.print(moistpercent);
  Serial.println("%");
  delay(2000);

  //Rain
  rainvalue = analogRead(rainfall);
  Serial.print("Raindrop Analog Value: ");
  Serial.println(rainvalue);
  rainpercent = map(rainvalue,0,1023,100,0);
  Serial.print("Raindrop Level Percentage: ");
  Serial.print(rainpercent);
  Serial.println("%"); 
  delay(2000);

  //DHT
  DHT.read11(dht_apin);
  dhthumid=DHT.humidity;
  Serial.print("Humidity: ");
  Serial.print(dhthumid);
  Serial.println("%  ");
  dhttemp=DHT.temperature;
  Serial.print("Temperature: ");
  Serial.print(dhttemp); 
  Serial.println("C  ");
  delay(2000);

/*
  //PUMP
  digitalWrite(RELAY_PIN, HIGH); 
  Serial.println("Relay ON");
  delay(2000);
  digitalWrite(RELAY_PIN, LOW);
  Serial.println("Relay OFF");
  delay(2000);
*/

/*
  //Touch
  if (digitalRead(2) == HIGH){
  Serial.println("Sensor is touched");
  }
  else {
  Serial.println("Sensor not touched");
  }
  delay(2000);
*/
 
/*
  //LDR
  ldrv=analogRead(ldr);
  Serial.print("LDR value:");
  Serial.println(ldrv);
  ldrpercent= map(ldrv,0,1023,100,0 );
  Serial.print("LDR Value Percent:");
  Serial.println(ldrpercent);
  delay(2000);
*/

/*
  //LCD
  lcd.setCursor(0,0);
  lcd.print("LCD Is");
  lcd.setCursor(0,1);
  lcd.print("Working");
  Serial.print("\n\n");
  delay(6000);
*/

  //Touch
  if (digitalRead(2) == HIGH){
  Serial.print("Soil Moisture:");
  Serial.println(moistpercent);
  lcd.setCursor(0,0);
  lcd.print("Moist %:");
  lcd.print(moistpercent);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("Have a Good Day");
  delay(5000);
  lcd.clear();
  }
  delay(2000);
 
  if (rainvalue<rainthresh | sensorValue<moistthresh){
    lcd.setCursor(0,0);
    lcd.print("Raining/Moist");
    lcd.setCursor(0,1);
    lcd.print("No water needed");
    delay(5000);
    lcd.clear();
  }
  else {
    if (digitalRead(2) == HIGH){
      Serial.print("Soil Moisture:");
      Serial.println(moistpercent);
      lcd.setCursor(0,0);
      lcd.print("Moist %:");
      lcd.print(moistpercent);
      lcd.print("%");
      lcd.setCursor(0,1);
      lcd.print("Have a Good Day");
      delay(5000);
      lcd.clear();
  }
    if (dhttemp>dhttempthresh & dhthumidthresh2>dhthumid){
      lcd.setCursor(0,0);
      lcd.print("V Hot Weather");
      lcd.setCursor(0,1);
      lcd.print("Watering..");
      digitalWrite(RELAY_PIN, LOW);
      delay(6000);
      digitalWrite(RELAY_PIN, HIGH);
      delay(5000);
      lcd.clear();
    }
    else if (dhttemp>dhttempthresh & dhthumidthresh2<dhthumid & dhthumid<dhthumidthresh){
      lcd.setCursor(0,0);
      lcd.print("Hot and Humid");
      lcd.setCursor(0,1);
      lcd.print("Watering..");
      digitalWrite(RELAY_PIN, LOW);
      delay(4000);
      digitalWrite(RELAY_PIN, HIGH);
      delay(5000);
      lcd.clear();
    }
    else if (dhttemp>dhttempthresh & dhthumid>dhthumidthresh){
      lcd.setCursor(0,0);
      lcd.print("V Hot & V Humid");
      lcd.setCursor(0,1);
      lcd.print("Watering..");
      digitalWrite(RELAY_PIN, LOW);
      delay(2000);
      digitalWrite(RELAY_PIN, HIGH);
      delay(5000);
      lcd.clear();
    }
   


    else if (dhttemp<dhttempthresh & dhthumidthresh2>dhthumid){
      lcd.setCursor(0,0);
      lcd.print("Cool Weather");
      lcd.setCursor(0,1);
      lcd.print("Watering..");
      digitalWrite(RELAY_PIN, LOW);
      delay(4000);
      digitalWrite(RELAY_PIN, HIGH);
      delay(5000);
      lcd.clear();
    }
    else if (dhttemp<dhttempthresh & dhthumidthresh2<dhthumid & dhthumid<dhthumidthresh){
      lcd.setCursor(0,0);
      lcd.print("Cool but Humid");
      lcd.setCursor(0,1);
      lcd.print("Watering..");
      digitalWrite(RELAY_PIN, LOW);
      delay(2000);
      digitalWrite(RELAY_PIN, HIGH);
      delay(5000);
      lcd.clear();
    }
    else if (dhttemp<dhttempthresh & dhthumid>dhthumidthresh){
      lcd.setCursor(0,0);
      lcd.print("Cool but VHumid");
      lcd.setCursor(0,1);
      lcd.print("Watering");
      digitalWrite(RELAY_PIN, LOW);
      delay(1000);
      digitalWrite(RELAY_PIN, HIGH);
      delay(5000);
      lcd.clear();
    }    
  }
}
