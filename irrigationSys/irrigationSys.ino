//PUMP
const int RELAY_PIN = A0;

//LDR
int ldr=A0;
int ldrv=0;
int ldrpercent;
int ldrthreshold=500;

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
int rainthresh=500;
//int set=10; (Set value for when using a buzzer)

//DHT
#include <dht.h>
#define dht_apin A3
dht DHT;
int dhttempthresh= 50;
int dhthumidthresh= 80;
int dhthumidthresh2= 40;
int dhttemp;
int dhthumid;

void setup() {
  Serial.begin(9600);
  delay(500);
  pinMode(RELAY_PIN, OUTPUT); //PUMP
  pinMode(2, INPUT); //Touch Sensor
  //Serial.println("DHT11 Humidity & temperature Sensor"); //DHT
  pinMode(rainfall,INPUT); //Raindrop Sensor
  pinMode(sensorPin, INPUT); //Moisture Sensor
  lcd.begin(); //LCD
  lcd.backlight(); //LCD
  delay(1000);
}

void loop(){
  //Moisture
  sensorValue = analogRead(sensorPin); 
  Serial.print("Soil Moisture Analog Value : ");
  Serial.println(sensorValue);
  moistpercent = map(sensorValue,0,1023,100,0);
  Serial.print("Soil Moisture Level Percentage: ");
  Serial.println(moistpercent);
  delay(2000);

  //Rain
  rainvalue = analogRead(rainfall);
  Serial.print("Raindrop Analog Value: ");
  Serial.println(rainvalue);
  rainpercent = map(rainvalue,0,1023,100,0);
  Serial.print("Raindrop Level Percentage: ");
  Serial.println(rainpercent);
  delay(2000);

  //DHT
  DHT.read11(dht_apin);
  DHT.humidity= dhthumid;
  Serial.print("Humidity: ");
  Serial.print(dhthumid);
  Serial.println("%  ");
  DHT.temperature= dhttemp;
  Serial.print("Temperature: ");
  Serial.print(dhttemp); 
  Serial.println("C  ");
  delay(2000);
  
  //PUMP
  digitalWrite(RELAY_PIN, HIGH); 
  Serial.println("Relay ON");
  delay(2000);
  digitalWrite(RELAY_PIN, LOW);
  Serial.println("Relay OFF");
  delay(2000);

  //Touch
  if (digitalRead(2) == HIGH){
  Serial.println("Sensor is touched");
  }
  else {
  Serial.println("Sensor not touched");
  }
  delay(2000);
 
  //LDR
  ldrv=analogRead(ldr);
  Serial.print("LDR value:");
  Serial.println(ldrv);
  ldrpercent= map(ldrv,0,1023,100,0 );
  Serial.print("LDR Value Percent:");
  Serial.println(ldrpercent);
  delay(2000);

  //LCD
  lcd.setCursor(0,0);
  lcd.print("LCD Is");
  lcd.setCursor(0,1);
  lcd.print("Working");
  Serial.print("\n\n");
  delay(6000);

  if (rainvalue<rainthresh | moistpercent>=80){
    lcd.setCursor(0,0);
    lcd.print("Raining/Moist");
    lcd.setCursor(0,1);
    lcd.print("No water needed");
  }
  else {
    if (dhttemp>dhttempthresh & ldrv==1 & dhthumidthresh2>dhthumid){
      lcd.setCursor(0,0);
      lcd.print("V Hot Weather");
      lcd.setCursor(0,1);
      lcd.print("Watering..");
      digitalWrite(RELAY_PIN, HIGH);
      delay(6000);
      digitalWrite(RELAY_PIN, LOW);
      delay(5000);
    }
    else if (dhttemp>dhttempthresh & ldrv==1 & dhthumidthresh2<dhthumid<dhthumidthresh){
      lcd.setCursor(0,0);
      lcd.print("Hot and Humid");
      lcd.setCursor(0,1);
      lcd.print("Watering..");
      digitalWrite(RELAY_PIN, HIGH);
      delay(4000);
      digitalWrite(RELAY_PIN, LOW);
      delay(5000);
    }
    else if (dhttemp>dhttempthresh & ldrv==1 & dhthumid>dhthumidthresh){
      lcd.setCursor(0,0);
      lcd.print("V Hot & V Humid");
      lcd.setCursor(0,1);
      lcd.print("Watering..");
      digitalWrite(RELAY_PIN, HIGH);
      delay(2000);
      digitalWrite(RELAY_PIN, LOW);
      delay(5000);
    }
   
    
    
    else if (dhttemp>dhttempthresh & ldrv==0 & dhthumidthresh2>dhthumid){
      lcd.setCursor(0,0);
      lcd.print("Cloudy but Hot");
      lcd.setCursor(0,1);
      lcd.print("Watering..");
      digitalWrite(RELAY_PIN, HIGH);
      delay(6000);
      digitalWrite(RELAY_PIN, LOW);
      delay(5000);
    }
    else if (dhttemp>dhttempthresh & ldrv==0 & dhthumidthresh2<dhthumid<dhthumidthresh){
      lcd.setCursor(0,0);
      lcd.print("Cloudy,Hot,Humid");
      lcd.setCursor(0,1);
      lcd.print("Watering..");
      digitalWrite(RELAY_PIN, HIGH);
      delay(4000);
      digitalWrite(RELAY_PIN, LOW);
      delay(5000);
    }
    else if (dhttemp>dhttempthresh & ldrv==0 & dhthumid>dhthumidthresh){
      lcd.setCursor(0,0);
      lcd.print("Cloudy,VHotHumid");
      lcd.setCursor(0,1);
      lcd.print("Watering..");
      digitalWrite(RELAY_PIN, HIGH);
      delay(2000);
      digitalWrite(RELAY_PIN, LOW);
      delay(5000);
    }



    else if (dhttemp<dhttempthresh & ldrv==0 & dhthumidthresh2>dhthumid){
      lcd.setCursor(0,0);
      lcd.print("Cool Weather");
      lcd.setCursor(0,1);
      lcd.print("Watering..");
      digitalWrite(RELAY_PIN, HIGH);
      delay(4000);
      digitalWrite(RELAY_PIN, LOW);
      delay(5000);
    }
    else if (dhttemp<dhttempthresh & ldrv==0 & dhthumidthresh2<dhthumid<dhthumidthresh){
      lcd.setCursor(0,0);
      lcd.print("Cool but Humid");
      lcd.setCursor(0,1);
      lcd.print("Watering..");
      digitalWrite(RELAY_PIN, HIGH);
      delay(2000);
      digitalWrite(RELAY_PIN, LOW);
      delay(5000);
    }
    else if (dhttemp<dhttempthresh & ldrv==0 & dhthumid>dhthumidthresh){
      lcd.setCursor(0,0);
      lcd.print("Cool but VHumid");
      lcd.setCursor(0,1);
      lcd.print("Watering");
      digitalWrite(RELAY_PIN, HIGH);
      delay(1000);
      digitalWrite(RELAY_PIN, LOW);
      delay(5000);
    }




    else if (dhttemp<dhttempthresh & ldrv==1 & dhthumidthresh2>dhthumid){
      lcd.setCursor(0,0);
      lcd.print("Sunny Weather");
      lcd.setCursor(0,1);
      lcd.print("Watering..");
      digitalWrite(RELAY_PIN, HIGH);
      delay(4000);
      digitalWrite(RELAY_PIN, LOW);
      delay(5000);
    }
    else if (dhttemp<dhttempthresh & ldrv==1 & dhthumidthresh2<dhthumid<dhthumidthresh){
      lcd.setCursor(0,0);
      lcd.print("Sunny and Humid");
      lcd.setCursor(0,1);
      lcd.print("Watering..");
      digitalWrite(RELAY_PIN, HIGH);
      delay(2000);
      digitalWrite(RELAY_PIN, LOW);
      delay(5000);
    }
    else if (dhttemp<dhttempthresh & ldrv==1 & dhthumid>dhthumidthresh){
      lcd.setCursor(0,0);
      lcd.print("Sunny & VHumid");
      lcd.setCursor(0,1);
      lcd.print("Watering");
      digitalWrite(RELAY_PIN, HIGH);
      delay(2000);
      digitalWrite(RELAY_PIN, LOW);
      delay(5000);
    }
    
}
  }
