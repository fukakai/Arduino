/**
* 
* @Author: Fukakai
* 02/06.2013
* Moving samples
*/

#include <Servo.h>
#include <NewPing.h>

int variator = 200;                  // Positive is turn under the direction of clockwise
                                     // Negative is turn on the oposite of the direction of clockwise

#define ULTRA_TRIGGER 11       // What pin we have connected the Ultrasonic range sensor Trigger pin
#define ULTRA_ECHO    11        // What pin we have connected the Ultrasonic range sensor Echo pin
#define MAX_DISTANCE 350        // Maximum distance we want to ping for (in centimeters). Most sensor are rated at 400-500cm.

Servo servoLeft;                     // Declare left and right servos
Servo servoRight;
unsigned long echoTime=0;
long int      distance=0;
const int pingPin = 7;
int led = 3;


NewPing sonar(ULTRA_TRIGGER, ULTRA_ECHO, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() { 
  servoLeft.attach(13);                     // Attach left wheel signal to pin 13
  servoRight.attach(12);                    // Attach right wheel signal to pin 12
  
  pinMode(led, OUTPUT); 
  
  pinMode(ULTRA_TRIGGER, OUTPUT);           //Create signal on this pin
  pinMode(ULTRA_ECHO, INPUT);              //Create signal on this pin
}

void loop() {
    
  echoTime = sonar.ping_median();  // We do 5 measurements to have a good average and filter bad measurements
  distance = sonar.convert_cm(echoTime);
  
  if(distance < 10){  
      digitalWrite(led, HIGH);  // sets the LED on
      delay(10);                // waits for a second
      digitalWrite(led, LOW);   // sets the LED off
      maneuver(0, 0, 1000);                     // Stop 3000 seconds
  }else{ 
    maneuver(-variator, -variator, 1000);      // Forward 1 seconds
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
