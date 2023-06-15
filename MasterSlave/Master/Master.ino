#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2); 

int ldr=A0;
int ldrvalue=0;
int ldrpercent;
int ldrthresh= 550;
int val;

void setup() {
  // Start the I2C Bus as Master
  Wire.begin(); 
  Serial.begin(9600);
  lcd.begin(); //LCD
  lcd.backlight(); //LCD
}
void loop() {
  ldrvalue=analogRead(ldr);
  Serial.print("LDR value:");
  Serial.println(ldrvalue);
  if (ldrvalue<ldrthresh){
    val = 0;
    lcd.setCursor(0,0);
    lcd.print("Cool Weather");
    lcd.setCursor(0,1);
    lcd.print("Water");
  }
  else {
    val = 1;
    lcd.setCursor(0,0);
    lcd.print("Hot Weather");
    lcd.setCursor(0,1);
    lcd.print("Watering..");
  }
  Serial.println(val);
  Wire.beginTransmission(9); // transmit to device #9
  Wire.write(val);              // sends ldrval 
  Wire.endTransmission();    // stop transmitting
  delay(2000);
}
