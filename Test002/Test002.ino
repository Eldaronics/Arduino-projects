#define trigPin 7
#define echoPin 6
#define buzzerPin 11
int r = 2;
int g = 3;
int b = 4;
int melody;
long duration, distance;
//char* CurrentDistance[3] = {"red","green","blue"};
int distanceDisplay = 1;
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  // Serial.begin(9600);
}
void loop()
{
  digitalWrite(trigPin, 0);
  delayMicroseconds(2);
  digitalWrite(trigPin, 1);
  delayMicroseconds(10);
  digitalWrite(trigPin, 0);
  duration = pulseIn(echoPin, 1);
  distance = (duration / 2) / 29.1;
  //Serial.print("The distance is:");
  //Serial.println(distance);
  //Serial.print(" Centimeters");
  distanceHandle();
}
void distanceHandle()
{
  if (distance < 180 && distance > 0)
  {
    //CurrentDistance[1] = "red";
    distanceDisplay = 1;
  }
  else if (distance < 290 && distance > 181)
  {
    //CurrentDistance[2] = "blue";
    distanceDisplay = 2;
  }
  else if (distance < 390 && distance > 291 && distance > 390)
  {
    //CurrentDistance[3] = "green";
    distanceDisplay = 3;
  }
  else
  {
    digitalWrite(r, 0);
    digitalWrite(g, 0);
    digitalWrite(b, 0);
    digitalWrite(buzzerPin, 0);
  }
  switch (distanceDisplay)
  {
    case 1:
      red();
      digitalWrite(b, 0);
      digitalWrite(g, 0);
      break;
    case 2:
      digitalWrite(b, 1);
      digitalWrite(r, 0);
      digitalWrite(g, 0);
      digitalWrite(buzzerPin, 0);
      break;
    case 3:
      digitalWrite(g, 1);
      digitalWrite(b, 0);
      digitalWrite(g, 0);
      digitalWrite(buzzerPin, 0);
      break;
  }
}
void red()
{
  melody = map(distance, 0, 180, 10, 100);
  digitalWrite(buzzerPin, 1);
  digitalWrite(r, 1);
  delay(melody);
  digitalWrite(buzzerPin, 0);
  digitalWrite(r, 0);
  delay(melody);
}

