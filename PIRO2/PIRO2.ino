#include <Servo.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
int lefteye = 5;
int righteye = 4;
Servo servo1;
void setup() {
  servo1.attach(3, 0, 2350);
  servo1.write(0);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(3), servo , CHANGE);
  Serial.begin (9600);
  mp3_set_serial (Serial);    //set Serial for DFPlayer-mini mp3 module
  mp3_set_volume (100);
  mp3_play (1);
}

void loop() {
  servo();
  eye();
}
void eye ()
{ digitalWrite( righteye, 0);
  digitalWrite(lefteye, 0);
  delay(100);
  digitalWrite( righteye, 1);
  digitalWrite(lefteye, 1);
  delay(3000);
}
void servo()
{
  int v = analogRead(A0);
  int d = map(v, 0, 1023, 0, 255);
  servo1.write(d);
}

