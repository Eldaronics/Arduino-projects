#include<avr/power.h>
#include <avr/sleep.h>
unsigned long timeVal;
unsigned long  alarmLim = 25200;
#define buzzerPin 6
void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  set_sleep_mode(SLEEP_MODE_IDLE);
  power_adc_disable();
  power_spi_disable();
  power_twi_disable();
}
void loop() {
  timeVal = (millis() / 1000);
  if (timeVal == alarmLim)
  {
    wakeUp();
  }
}

void wakeUp() {
  while (1)
  {
    tone(buzzerPin, 550);
    digitalWrite(11, 1);
    delay(1000);
    digitalWrite(13, 1);
    noTone(buzzerPin);
    delay(1000);
    digitalWrite(11, 0);
    digitalWrite(13, 0);
  }
}

