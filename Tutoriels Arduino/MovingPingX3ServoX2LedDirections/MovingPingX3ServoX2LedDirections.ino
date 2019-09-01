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
#define MAX_PING_DISTANCE 800                            // power

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
                                       
void setup() {
  //led
  pinMode(led, OUTPUT); 
  
  //sonar
  Serial.begin(115200);
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object                 // in steps of 1 degree 
  myservo.write(0);
    
  //wheels
  servoLeft.attach(13);                     // Attach left wheel signal to pin 13
  servoRight.attach(12);                    // Attach right wheel signal to pin 12
}
 
void loop() {
  pos=(pos+60)%180;                  //5 arrêts
  myservo.write(pos);

  maneuver(0, 0, 1000);      // Forward 1 seconds 
  
  //delay(500);
  int uS = sonar.ping_median(5);
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM);
  Serial.println("cm");
  
  //delay(50);
  if((uS / US_ROUNDTRIP_CM) < distance_for_reaction){
    digitalWrite(3, HIGH);  
    delay(50);    
    digitalWrite(3, LOW); 
    maneuver(variator, variator, 2000);      // Backward 1 seconds
  }else{
    maneuver(-variator, -variator, 2000);      // Forward 1 seconds   
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
