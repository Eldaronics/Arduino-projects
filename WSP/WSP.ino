#include <Wire.h>
#include <LiquidCrystal_I2C.h>
int alarmv = 200;
int v;               //value(temp)
int tempPin = A1;
int wsPin = A0;
float highv = -50;
float lowv = 100;
byte symbol[8]
{
  B11100,
  B10100,
  B11100,
  B00000,
  B00000,
  B00000,
  B00000,
};
LiquidCrystal_I2C lcd (0x27, 16, 2);
void setup() {
  lcd.begin();
  lcd.clear();
  analogReference(INTERNAL);
  lcd.createChar(0, symbol);

  // Serial.begin(9600);
}

void loop() {
  lcd.home();
  v = analogRead(tempPin);
  float d = (v / 1024.0) * 1000;
  float cel = d / 10;
  //Serial.println(cel);
  lcd.print("Current: ");
  lcd.print(cel);
  lcd.write(byte(0));
  lcd.print(" ");
  lcd.setCursor(0, 16);
  if (cel > highv)
  {
    highv = cel;
  }
  lcd.print("H:");
  lcd.print(highv);
  lcd.write(byte(0));
  lcd.print(" ");
  lcd.setCursor(8, 16);
  if (cel < lowv)
  {
    lowv = cel;
  }
  lcd.print("L:");
  lcd.print(lowv);
  lcd.write(byte(0));
  lcd.print(" ");
  delay(400);
}
