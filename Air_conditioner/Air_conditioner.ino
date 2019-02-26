#include <IRremote.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>                //A4 goes to SDA(Serial Data Line and SCL means Serial Clock Line)
#include <EEPROM.h>
#include <Servo.h>
#define lcdLight = A4;
#define pwrIR 0xFF30CF
#define okIR 0xFF02FD
#define upIR 0xFFE21D
#define downIR 0xFF40BF
#define stanbyIR  0xFF00FF
#define saveIR 0xFF20DF
#define lcdStandby 0xFFE817
int v;                          //value(temp)
int servo_angle = EEPROM.get(0, servo_angle);
const int tempPin = A1;
const int waterPin = A0;
const int fanCtrlPin = 10;
const int buzzerPin = 11;
const int IRPin = 2;
const int servoPin = 6;
unsigned long previousMillis;
unsigned long currentMillis = millis();
const long interval = 1000;
volatile bool interruptTrig = 0;
bool trig = 1;
bool lcdTrig = 1;
bool servoTrig = 1;
Servo servo;
decode_results results;
IRrecv irrecv(IRPin);
byte symbol[8]
{B11100, B10100, B11100, B00000, B00000, B00000, B00000, B00000,};
byte upwards[8]
{B00100, B01110, B11111, B00100, B00100, B00100, B00100, B00100,};
byte downwards[8]
{B00100, B00100, B00100, B00100, B00100, B11111, B01110, B00100,};
byte straight[8]
{B00000, B00000, B00000, B00000, B11111, B00000, B00000, B00000,};
byte up [8]
{B00010, B00100, B01000, B10000, B00000, B00000, B00000, B00000,};
byte top [8]
{B00100, B01000, B10000, B00000, B00000, B00000, B00000, B00000,};
byte down  [8]
{B00000, B00000, B00000, B00000, B10000, B01000, B00100, B00010,};
byte bottom [8]
{ B00000, B00000, B00000, B00000, B00000, B10000, B01000, B00100,};
byte sym[8]
{B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111,};
byte sym1[8]
{B10001, B10001, B10001, B10001, B10001, B10001, B10001, B10001,};
LiquidCrystal_I2C lcd (0x27, 16, 2);
void setup() {
  {
    irrecv.enableIRIn();
    irrecv.blink13(1);
  }
  pinMode(fanCtrlPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  {
    lcd.begin();
    lcd.clear();
    lcd.print("   Eldaronics");
    lcd.setCursor(0, 1);
    lcd.print("Have a cool day!");
    delay(200);
    lcd.createChar(0, symbol);
    lcd.createChar(1, upwards);
    lcd.createChar(2, downwards);
    lcd.createChar(3, straight);
    lcd.createChar(4, up);
    lcd.createChar(5, down);
    lcd.createChar(6, bottom);
    lcd.createChar(7, top);
    delay(200);
    lcd.clear();
  }
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), angle_IR, CHANGE);
  servo.attach(6, 1600, 2300);
  analogReference(INTERNAL);
  Serial.println("angle value while starting: ");
  Serial.println(servo_angle);
  servo.write(servo_angle);
}
void loop() {
  lcd.home();
  {
    digitalWrite(buzzerPin, 0);
    digitalWrite(fanCtrlPin, trig);
    lcd.setCursor(15, 0);
    lcd.print(" ");
  }
  v = analogRead(tempPin);
  float d = (v / 1024.0) * 1000;
  int cel = d / 10;
  int fah = (cel * 9 / 5) + 32;
  int wtrValue = map(waterPin, 0, 1023, 0, 100);
  {
    lcd.setCursor(0, 0);
    lcd.print("C:");
    lcd.print(cel);
    lcd.write(byte(0));
    lcd.print(" ");
    lcd.setCursor(6, 0);
    lcd.print("F:");
    lcd.print(fah);
    lcd.write(byte(0));
    lcd.print(" ");
    lcd.setCursor(0, 1);
    lcd.print("Water level:");
    lcd.print(wtrValue);
    lcd.print("%");
    lcd.print("  ");
  }
  //auto_angle();
  angle_limit();
  //angle_IR();
  angle_informer();
  // servo_angle++;
  delay(200);
}
void angle_limit()
{
  if (servo_angle >= 2300 )
  {
    servo_angle = 2300;
    servo_angle -= 50;
  }
  if (servo_angle <= 1600)
  {
    servo_angle = 1600;
    servo_angle += 50;
  }
}
void angle_informer()
{
  if (servo_angle >= 1550 && servo_angle <= 1700 )
  {
    lcd.setCursor(13, 0);
    lcd.write(byte(6));
  }
  if (servo_angle >= 1701 && servo_angle <= 1900)
  {
    lcd.setCursor(13, 0);
    lcd.write(byte(5));
  }
  if (servo_angle >= 1801 && servo_angle <= 1900)
  {
    lcd.setCursor(13, 0);
    lcd.write(byte(3));
  }
  if (servo_angle >= 1901 && servo_angle <= 2150)
  {
    lcd.setCursor(13, 0);
    lcd.write(byte(4));
  }
  if (servo_angle >= 2151 && servo_angle <= 2300)
  {
    lcd.setCursor(13, 0);
    lcd.write(byte(7));
  }
}
void angle_IR()
{
  interruptTrig = !(interruptTrig);
  if (irrecv.decode(&results))
  {
    if (results.value == upIR)
    {
      lcd.home();
      digitalWrite(buzzerPin, 1);
      servo_angle += 50;
      servo.write(servo_angle);
      Serial.print("servo angle:");
      Serial.println(servo_angle);
      lcd.setCursor(15, 0);
      lcd.write(byte(1));
      lcd.home();
      // delay(150);
      // lcd.clear();
    }
    if (results.value == downIR)
    {
      lcd.home();
      digitalWrite(buzzerPin, 1);
      servo_angle -= 50;
      servo.write(servo_angle);
      Serial.print("servo angle:");
      Serial.println(servo_angle);
      lcd.setCursor(15, 0);
      lcd.write(byte(2));
      lcd.home();
      // delay(150);
      // lcd.clear();

    }
    if (results.value == saveIR)
    {
      digitalWrite(buzzerPin, 1);
      EEPROM.put(0, servo_angle);
      Serial.println("unsaved: ");
      Serial.println(servo_angle);
      Serial.println("saved: ");
      Serial.println(EEPROM.get(0, servo_angle));
    }
    if (results.value == pwrIR)
    {
      digitalWrite(buzzerPin, 1);
      delay(500);
      trig = !(trig);
      power();
    }
    if (results.value == okIR)
    {
      digitalWrite(buzzerPin, 1);
      auto_angle();
    }
    if (results.value == stanbyIR)
    {
      digitalWrite(buzzerPin, 1);
      lcdTrig =  !(lcdTrig);
      lcd_trigger();
    }
    if (results.value == lcdStandby)
    {
      digitalWrite(buzzerPin, 1);
      trig = !(trig);
      servoTrig = !(servoTrig);
      servo_trigger();
    }
  }
  irrecv.resume();
}
void auto_angle()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > interval)
  {
    previousMillis = currentMillis;
    /*
      if (servo_angle >= 2200)
      servo_angle -= 100;
      if (servo_angle <= 1700)
      servo_angle += 50;
      else
    */

    /*
      for (servo_angle; servo_angle <= 2300;servo_angle += 1)
      {
      servo.write(servo_angle);
      delay(15);
      }
      for (servo_angle; servo_angle >= 1600; servo_angle -= 1)
      {
      servo.write(servo_angle);
      delay(15);
      }
    */
  }
}
void power()
{
  if (trig == 1)  {
    lcd.backlight();
    lcd.display();
    servo.attach(6);
  }
  else {
    lcd.noBacklight();
    lcd.noDisplay();
    servo.detach();
  }
}
void lcd_trigger()
{
  if (lcdTrig == 1) {
    lcd.backlight();
    lcd.display();
  }
  else  {
    lcd.noBacklight();
    lcd.noDisplay();
  }
}
void servo_trigger() {
  if (servoTrig == 1)
  {
    servo.attach(6);
  }
  else
  {
    servo.detach();
  }
}
