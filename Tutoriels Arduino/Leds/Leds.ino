/**
* 
* @Author: Fukakai
* 02/06.2013
* Moving samples
*/

/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 3;

// the setup routine runs once when you press reset:
void setup() {             
    pinMode(led, OUTPUT); 
}

// the loop routine runs over and over again forever:
void loop() { 
    digitalWrite(3, HIGH);  
    delay(200);    
    digitalWrite(3, LOW); 
    delay(200);    
    digitalWrite(3, HIGH); 
    delay(3000);    
}
