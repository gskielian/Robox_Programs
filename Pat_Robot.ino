
//DESCRIPTION
//
//A Patrol Robot -- Feel free to hack this code!

//WIRING
//
//Ultrasonic was connected with
//vcc     -> 5v
//trigPin -> digital 12
//echoPin -> digital 13
//Gnd     -> gnd
//
//Servos pwm wire (the white or yellow wire) connects to digital pins 5 and 6 (if the robot rolls backwards, simply swap the 5 and 6 wires).
//Servos' red wires  -> 5v
//Servos' black or brown wire -> GND



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

//Movement functions
void goForward()
{
    LeftW.write(120); // change this to 180 for full speed
    RightW.write(60); // change this to 0 for full speed
}

void goBackward()
{
    LeftW.write(60);
    RightW.write(120);
}


//Ultrasonic code
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

