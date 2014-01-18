//Ice Cooler Robot
//this is just the same robox parts hot glued to a ice-chest that's filled with drinks
//this particular robot uses this remote/receiver http://www.adafruit.com/products/1095 && http://www.adafruit.com/products/1097

//Wiring
//  pinMode(13,OUTPUT); // Connect VCC here
//  digitalWrite(13, HIGH); // Power module form pin 13
//  pinMode(12,INPUT); 
//  pinMode(11,INPUT);
//  pinMode(10,INPUT);
//  pinMode( 9,INPUT);
//
// int LWPin = 5; //connect digital 5 to left-wheel pin
// int RWPin = 6; //right-wheel control pin



double ForwardSpeed = 30.0;
double RotateSpeed = 30.0;
double BackwardSpeed = 30.0;

#include <Servo.h> 
 
Servo LeftWheel;  // create servo object to control a servo 
Servo RightWheel;  // create servo object to control a servo 

// Note: a maximum of eight servo objects can be created 

int LWPin = 5; //left-wheel control pin (if they spin in reverse, one fix is to switch it so RWPin=5 and LWPin=6)
int RWPin = 6; //right-wheel control pin



void setup() 
{ 
  LeftWheel.attach( LWPin );  //  Connects LeftWheel to the pin LWPin
  RightWheel.attach( RWPin );  // Connects another wheel to be controlled by the pin RWPin
  pinMode(13,OUTPUT);
  pinMode(12,INPUT);
  pinMode(11,INPUT);
  pinMode(10,INPUT);
  pinMode( 9,INPUT);
  
  digitalWrite(13,HIGH);
} 
 
 
void loop() 
{ 



     if ( digitalRead(9) == HIGH && digitalRead(10) == HIGH && digitalRead(11) == HIGH && digitalRead(12) == HIGH) {
        RotateLeft(2); //the argument of each directional command is the duration of movement in seconds
        Forward(1); 
     }
     else if ( digitalRead(11) == HIGH && digitalRead(12) == HIGH) {
      RotateRight(1);
      RotateLeft(2);
      Forward(1);
      Backward(1);    
     }
     //The Basic Controls
     else if ( digitalRead(9) == HIGH && digitalRead(10) == HIGH) {
      Stop(0.1);  
     }
     else if ( digitalRead(9) == HIGH) {       
       Forward(0.1); 
     }
     else if ( digitalRead(10) == HIGH) {
       RotateLeft(0.1);
     }
     else if ( digitalRead(11) == HIGH) {
       Backward(0.1); 
     }
     else if ( digitalRead(12) == HIGH) {
       RotateRight(0.1); 
     }
     else {
      Stop(0.1); 
     }
     //end basic controls
 
   //  Backward(4);
   //  RotateLeft(2);
   //  RotateRight(2);
   //  Stop(3);
    
     
} 

















//Robox Code

void Forward(double seconds)
{
    double speed = ForwardSpeed;

     attachServos(); //in case we disconnected them

     //The CRS thinks it is always at 90 degrees
     //if you tell it to go to 180 degrees it will go really fast clock-wise
     //0 degrees really quickly counterclockwise
     // 95 really slowly clockwise
     
    double leftspeed = (-speed/100.0*90.0 + 90) ;
    double rightspeed = (speed/100.0*90.0 + 90) ;  // translates it to servo-speak (servo input is from 0-180)
    
    LeftWheel.write( (int) leftspeed);             
    RightWheel.write((int) rightspeed); // Right wheel is backwards
 
   //delay wants an integer number of milliseconds, we turn seconds to milliseconds
   //then we turn the result into an int
   delay((int) (seconds*1000)); 
}



void Backward ( double seconds)
{
    double speed = BackwardSpeed; 

    attachServos(); //in case we disconnected them

    double leftspeed = (speed/100.0*90.0 + 90) ;
    double rightspeed = (-speed/100.0*90.0 + 90) ;  // translates it to servo-speak (servo input is from 0-180)
    
    LeftWheel.write( (int) leftspeed);             
    RightWheel.write((int) rightspeed);
    
    delay((int) (seconds*1000));
}



void RotateLeft (double seconds)
{
    double speed = RotateSpeed;

    attachServos(); //in case we disconnected them

    double leftspeed = (speed/100.0*90.0 + 90) ;  // translates it to servo-speak (servo input is from 0-180)
    double rightspeed = (speed/100.0*90.0 + 90) ;  // translates it to servo-speak (servo input is from 0-180)
    
    LeftWheel.write((int) leftspeed);             
    RightWheel.write((int) rightspeed);
    delay((int) (seconds*1000));
}

void RotateRight (double seconds)
{
    double speed = RotateSpeed;
    
    attachServos(); //in case we disconnected them
     
    double leftspeed =  (-speed/100.0*90.0 + 90) ;  // translates it to servo-speak (servo input is from 0-180)
    double rightspeed =  (-speed/100.0*90.0 + 90) ;  // translates it to servo-speak (servo input is from 0-180)
    
    LeftWheel.write((int) leftspeed);             
    RightWheel.write((int) rightspeed); 

    delay((int) (seconds*1000));
}


void Stop( double seconds)
{
  LeftWheel.detach();  //to stop the motors, we have the Arduino stop sending signals entirely
  RightWheel.detach();

  delay((int) (seconds*1000));
}





void attachServos()
{
   LeftWheel.attach(LWPin);
   RightWheel.attach(RWPin);
}
