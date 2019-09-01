/**
* 
* @Author: Fukakai
* 02/06.2013
* Moving samples
*/

#include <Servo.h>

int variator = 200;                  // Positive is turn under the direction of clockwise
                                     // Negative is turn on the oposite of the direction of clockwise

Servo servoLeft;                     // Declare left and right servos
Servo servoRight;

void setup() { 
  servoLeft.attach(13);                     // Attach left wheel signal to pin 13
  servoRight.attach(12);                    // Attach right wheel signal to pin 12
}

void loop() {
  maneuver(variator, variator, 1000);        // Back 2 seconds
  maneuver(variator, -variator, 1000);       // Right 1 seconds
  maneuver(-variator, variator, 1000);       // Left 1 seconds
  maneuver(-variator, -variator, 1000);      // Forward 1 seconds
  maneuver(0, 0, 1000);                      // Stop 3 seconds
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
  delay(msTime);                                   // Delay for msTime
}
