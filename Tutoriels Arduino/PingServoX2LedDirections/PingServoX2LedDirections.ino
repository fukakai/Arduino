/**
* 
* @Author: Fukakai
* 03.06.2013
* Ping, servo, led and directions
*/
#include <NewPing.h>                                     //NewPing library
#include <Servo.h>                                       //Wheel Servo Library

#define TRIGGER_PIN  11                                  //listener pin
#define ECHO_PIN     11                                  //active pin
#define MAX_PING_DISTANCE 200                            // power

//Led
int led = 3;                                              //led pin

//sonar
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_PING_DISTANCE);  //sonar declaration
int distance_for_reaction = 20;                           // in centimeters 
int pos = 0;    // variable to store the servo position 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
//wheels
Servo servoLeft;                                         // Left Wheel
Servo servoRight;                                        // Right Wheel
int variator = 200;                                      // Positive is turn under the direction of clockwise
                                                         // Negative is turn on the oposite of the direction of clockwise
                                                         
int uS = 0;

void setup() {
  //led
  pinMode(led, OUTPUT); 
  
  //sonar
  Serial.begin(115200);
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object                 // in steps of 1 degree 
  myservo.write(pos);
    
  //wheels
  servoLeft.attach(13);                     // Attach left wheel signal to pin 13
  servoRight.attach(12);                    // Attach right wheel signal to pin 12
}
 
void loop() {
  pos=(pos+36)%180;                  //5 arrêts
  maneuver(0, 0, 160);      // Forward 1 seconds 

  if(sonar.ping_cm() < distance_for_reaction){
    digitalWrite(led, HIGH);  
    delay(50);    
    digitalWrite(led, LOW); 
    maneuver(variator, variator, 2000);      // Backward 1 seconds
    myservo.write(pos);
  }else{
    maneuver(-variator, -variator, 2000);      // Forward 1 seconds 
    myservo.write(pos);
  }
  
}

void maneuver(int speedLeft, int speedRight, int msTime)
{
  // speedLeft, speedRight ranges: Backward  Linear  Stop  Linear   Forward
  //                               -200      -100......0......100       200
  servoLeft.writeMicroseconds(1500 + speedLeft);   // Set Left servo speed
  servoRight.writeMicroseconds(1500 - speedRight); // Set right servo speed
  if(msTime==-1)                                   // if msTime = -1
  {                                  
    servoLeft.detach();                            // Stop servo signals
    servoRight.detach();   
  }
  delay(msTime);                                   // Delay for msTime}
}
