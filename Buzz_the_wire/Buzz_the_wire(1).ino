/*
   Buzz the wire!With arduino
*/

#include <MaxMatrix.h> // download->>  https://github.com/riyas-org/max7219
#include "fonts.h"
#include <LedControl.h>
#include "pitches.h"
//Deyishenler - Variables
int numOfDev = 1;
String str = "";
byte buffer[10];
byte score_count = 1;
int d = 0;
//Pinler - Pins
int relay = 4;
int buzzer = 3;
int victorypin = 7;
int wireloop = 2;
int touching_melody = 225;
const int DIN = 12;   // DIN pin of MAX7219 module
const int CLK = 10;   // CLK pin of MAX7219 module
const int CS = 11;    // CS pin of MAX7219 module
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};
byte  smiley_touched[8] = {0xE0, 0xA6, 0xA6, 0xA0, 0xA0, 0xA6, 0xA6, 0xE0,};
byte smiley_intro[8] = {0xE0, 0xC6, 0xC6, 0xC0, 0xC0, 0xC6, 0xC6, 0xE0,};
byte smiley_happy[8] = {0x20,0x66,0xA6,0xA0,0xA0,0xA6,0x66,0x20,};
byte smiley_normal[8] = {0x00,0xC6,0xC6,0xC0,0xC0,0xC6,0xC6,0x00,};
byte smiley_sad[8] = {0x00,0x44,0x24,0x20,0x20,0x24,0x44,0x00,};
// Obyekt icrasi - Object Declaration
MaxMatrix m(DIN, CS, CLK, numOfDev);
LedControl lc = LedControl(DIN, CLK, CS, 0);
// Metnler
char text_intro[] = "22";
//char text_victory[] = "Siz qalibsiniz!!!";
char text_separator1[] = "   ";

char text_separator6[] = " ";
char text_count[5] = "0"; // initial count value

void setup() {

  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(victorypin, INPUT);
  pinMode(wireloop, INPUT);
  pinMode(relay, OUTPUT);
  lc.shutdown(0, false);      //The MAX72XX is in power-saving mode on startup
  lc.setIntensity(0, 15);     // Set the brightness to maximum value
  lc.clearDisplay(0);
  m.init();                   // module initialize// and clear the display
  m.setIntensity(15); // dot matix intensity 0-15
  printByte(smiley_intro);
  tone(buzzer,250);
  delay(120);
  noTone(buzzer);
}
void loop()
{

  if ((digitalRead(wireloop) == 1))
  {  
       // touching_melody+=50;
    digitalWrite(13, 1);
    digitalWrite(relay, 1);
    tone(buzzer,touching_melody+=25);
    printByte(smiley_touched);
    delay(1000);
    noTone(buzzer);
    digitalWrite(13, 0);
    digitalWrite(relay, 0);
    Serial.println(score_count);
      Serial.println(touching_melody);
    printByte(smiley_intro);
    score_count++;
   smiley();
  }
  if (digitalRead(victorypin) == 1)
  {
      for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzer, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 0.70;
    delay(pauseBetweenNotes);
    noTone(buzzer);
  }
    printByte(smiley_happy);
    digitalWrite(relay, 0);
    delay(2500);
    lc.clearDisplay(0);
    score_count--;
    str = String(score_count);
    str.toCharArray(text_count, 3);
    Serial.println(score_count);
    printStringWithShift(text_separator1, 50);
    printStringWithShift(text_count, 50);
    printStringWithShift(text_separator6, 50);
    c_printing();
  }

}
void printByte(byte character [])
{
  int i = 0;
  for (i = 0; i < 8; i++)
  {
    lc.setRow(0, i, character[i]);
  }

}
// Display=the extracted characters with scrolling
void printCharWithShift(char c, int shift_speed)
{
  if (c < 32) return;
  c -= 32;
  memcpy_P(buffer, CH + 7 * c, 7);
  m.writeSprite(33, 0, buffer);
  m.setColumn(33 + buffer[0], 0);
  for (int i = 0; i < buffer[0] + 1; i++)
  {
    delay(shift_speed);
    m.shiftLeft(false, false);
  }
}
void c_printing()
{
  while (1) {
    printStringWithShift(text_separator1, 50);
    printStringWithShift(text_count, 45);
    printStringWithShift(text_separator6, 50);
  }
}
void printStringWithShift(char* s, int shift_speed)
{
  while (*s != 0) {
    printCharWithShift(*s, shift_speed);
    s++;
  }
}
void smiley()
{
  if (score_count >= 11 && score_count <= 99)
    printByte(smiley_sad);
  else if (score_count >= 5 && score_count <= 10)
    printByte(smiley_normal);
   else if (score_count >= 0 && score_count <= 4)
    printByte(smiley_happy);
}

