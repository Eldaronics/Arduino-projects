#include <EEPROM.h>
int val;
int romadress = EEPROM.get(1000,romadress);
int TempPin = A0;
void setup() {
 Serial.begin(9600);
 Serial.print("Eeprom with Arduino :)");
 analogReference(INTERNAL);
}
void loop() {
 val = analogRead(TempPin);
 float tval=(val/1024.0)*1000;
 float cel = tval/10;
EEPROM.put(romadress,cel);
romadress+=4;
EEPROM.put(1000,romadress);

if (romadress>995)
romadress = 0;
if (Serial.available()>0)
{
 char SerialControl = Serial.read();
 if (SerialControl =='1') 
 
}
}
