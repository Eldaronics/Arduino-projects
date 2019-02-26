
void setup() {
Serial.begin(9600);
pinMode(10,OUTPUT);
}
void loop() {
  int pv =  map(analogRead(A0),0,1023,0,1800);
  tone(10,pv);
  //Serial.println("Analog Value: ");
  //Serial.println(pv);
  delay(200);

}
