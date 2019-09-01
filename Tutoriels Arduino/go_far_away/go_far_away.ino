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
#define MAX_PING_DISTANCE 300                            // power

//Led
int led = 3;                                              //led pin

//sonar
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_PING_DISTANCE);  //sonar declaration
int distance_for_reaction = 20;                           // in centimeters 
int pos = 150;    // variable to store the servo position 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
//savec values for 1 scan
int scan_values[5];
int position_values[5];

//wheels
Servo servoLeft;                                         // Left Wheel
Servo servoRight;                                        // Right Wheel
int variator = 200;                                      // Positive is turn under the direction of clockwise
                                                         // Negative is turn on the oposite of the direction of clockwise
int little_variator = variator/10;                       // Positive is turn under the direction of clockwise
                                                         // Negative is turn on the oposite of the direction of clockwise
                                       
//other
int way_find = 0;                                        //if this number is not reset to 0 and arrive to 6, we can't find a way to go, so, go back !

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
  
  maneuver(0, 0, 1000);      // Forward 1 seconds 
  
  for(int i=0;i<5;i++){
    
    pos=(pos+40)%180;                  // 
    myservo.write(pos);
     
    Serial.print("i = ");
    Serial.println(i);
    if(i==0){
      delay(1000);
    }else{ 
      delay(200);
    }
    
    int uS = sonar.ping();
    
    delay(300);

    
    scan_values[i]=uS / US_ROUNDTRIP_CM;
    position_values[i]=pos;  
    Serial.print("pos : ");
    Serial.print(pos);
    Serial.print(" - DIST IN CENTIMERS : ");
    Serial.print(scan_values[i]);
    Serial.println(" ");
  }
  int highest_value_index = 0;
  int highest_value = 0;
  int current_value = 0;
  int current_position = 0;
  
  for( int i=0; i < 5; i++){
    current_value = scan_values[i];
    if(current_value > highest_value){
      highest_value = current_value;
      highest_value_index =  i;
    }
  }
    Serial.print("Highest Value : ");
    Serial.print(highest_value);
    Serial.print(" - index : ");
    Serial.print(highest_value_index);
    Serial.print(" - Go to : ");
    Serial.print(position_values[highest_value_index]);
    Serial.println();
  
  go_away(position_values[highest_value_index],highest_value); 
}

void go_away(int pos,int dist){
  //cycle is : 10-50-90-130-170 and 30-70-110-150-10
  //cycle is : 0-40-80-120-160 and 20-60-100-140-0
  if(dist > distance_for_reaction){
    switch (pos) {
      case 10:                                      
        maneuver(variator, 0, 1000);                         // FULL RIGHT 1 seconds
        maneuver(-variator, -variator, 3000);                // GO FORWARD 1 seconds
        way_find = 0;                                        // we can move ! YEAH ! so, we need to search new directions and reset this to 0;
        break;
      case 30:
        maneuver(variator, 0, 1000);                         // FULL RIGHT 1 seconds
        maneuver(-variator, -variator, 3000);                // GO FORWARD 1 seconds
        way_find = 0;                                        // we can move ! YEAH ! so, we need to search new directions and reset this to 0;
        break;
      case 50:
        maneuver(little_variator, -little_variator, 1000);   // LITTLE Right 1 seconds
        maneuver(-variator, -variator, 3000);                // GO FORWARD 1 seconds
        way_find = 0;                                        // we can move ! YEAH ! so, we need to search new directions and reset this to 0;
        break;
      case 70:
        maneuver(little_variator, -little_variator, 1000);   // LITTLE Right 1 seconds
        maneuver(-variator, -variator, 3000);                // GO FORWARD 1 seconds
        way_find = 0;                                        // we can move ! YEAH ! so, we need to search new directions and reset this to 0;
        break;
      case 90:                                    
        maneuver(-variator, -variator, 3000);                // FULL CENTER 1 seconds
        way_find = 0;                                        // we can move ! YEAH ! so, we need to search new directions and reset this to 0;
        break;
      case 110:
        maneuver(-little_variator, little_variator, 1000);   // LITTLE LEFT 1 seconds
        maneuver(-variator, -variator, 3000);                // GO FORWARD 1 seconds
        way_find = 0;                                        // we can move ! YEAH ! so, we need to search new directions and reset this to 0;
        break;
      case 130:
        maneuver(-little_variator, little_variator, 1000);   // LITTLE LEFT 1 seconds
        maneuver(-variator, -variator, 3000);                // GO FORWARD 1 seconds
        way_find = 0;                                        // we can move ! YEAH ! so, we need to search new directions and reset this to 0;
        break;
      case 150:
        maneuver(-0, variator, 1000);                        // FULL LEFT 1 seconds
        maneuver(-variator, -variator, 3000);                // GO FORWARD 1 seconds
        way_find = 0;                                        // we can move ! YEAH ! so, we need to search new directions and reset this to 0;
        break;
      case 170:                                              // FULL LEFT
        maneuver(-0, variator, 1000);                        // Left 1 seconds
        maneuver(-variator, -variator, 3000);                // GO FORWARD 1 seconds
        way_find = 0;                                        // we can move ! YEAH ! so, we need to search new directions and reset this to 0;
        break;
      default: break;
        // if nothing else matches, do the default
        // default is optional
    }
  }else{
      way_find++;                                //the direction cannot be used, so we save it, if this number > 5, we hav'nt find a good way and we need to go back !
      if(way_find > 5){
        maneuver(variator, variator, 1000);        // Back 2 seconds
      }
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

int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}


