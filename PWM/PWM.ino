#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27, 16, 2);
void setup() {
  pinMode(11, OUTPUT);
  //Serial.begin(9600);
  lcd.begin();
  lcd.clear();
}
void loop() {
  int pv0 = map(analogRead(A0), 0, 1023, 0, 255);
  int pv1 = map(analogRead(A1), 0, 1023, 0, 255);
  lcd.home();
  float mv0 = pv0/2.55;
    float mv1 = pv1/2.55;
  analogWrite(11, pv0);
  lcd.print("1: ");
  lcd.print(mv0);
  lcd.print(" %");
  lcd.print(" ");
  lcd.setCursor(0, 16);
  lcd.print("2: ");
  lcd.print(mv1);
  lcd.print(" %");
  lcd.print(" ");
  lcd.noCursor();
  delay(1000);
}
