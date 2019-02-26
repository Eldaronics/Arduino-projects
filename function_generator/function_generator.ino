#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27, 16, 2);
int speaker=7;
void setup()
{
pinMode(7,OUTPUT);
lcd.begin();
lcd.home();
lcd.print("Configuring...");
delay(2000);
}
void loop()
{
int frequency = map(analogRead(A2),0,1023,0,1000);
lcd.home();
lcd.print("Frequency:");
lcd.print(frequency);
lcd.print(" Hz");
lcd.print(" ");
lcd.setCursor(0,16);
lcd.print("Wave generator");
tone(speaker,frequency);
lcd.noCursor();
delay(100);
}

