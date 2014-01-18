//TrigPin to Pin 12
//EchoPin to Pin 13

#include <Servo.h>
int trigPin = 12;
int echoPin = 13;

long cm;
long duration;
long distance;

Servo LeftW;
Servo RightW;

int time_until_wall=0;

void setup()
{
  LeftW.attach(5);
  RightW.attach(6);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}


void loop()
{
  cm = getDistance();
  if (cm < 5){
    Serial.println("backing up");
    goBackward();
    delay(time_until_wall);
    time_until_wall = 0;
  }
  else{
    goForward();
    delay(200);
    time_until_wall += 200;
   }
  Serial.println(time_until_wall);
}


void goForward()
{
    LeftW.write(120);
    RightW.write(60);
}

void goBackward()
{
    LeftW.write(60);
    RightW.write(120);
}

long getDistance()
{
  delay(10);
  //trigger the device
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

//how long it has been since we sent the ping
  duration = pulseIn(echoPin, HIGH);

//convert the duration to centimeters ( div by 2 because to and frro)
  cm = duration/27/2;
  return cm;
}

