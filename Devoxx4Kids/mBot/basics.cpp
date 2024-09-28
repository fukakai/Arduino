// Discover Arduino Uno Programmation

// #################################################################################################
// Écrire dans le Serial Monitor
// Write into the Serial Monitor


// Select in Arduino:
//  - Carriage Return
//  - 9600 BAUD

// Serial.print() - Write into the console
// F() -  pass flash-memory based strings
// \n - return to line
Serial.print(F("Hello World \n"));

// #################################################################################################
// Jouer une note
// Play a note

// 8 - pin
// 4978 - note
// 1000 - duration = 1 second
tone(8, 4978, 1000);
// #################################################################################################

// #################################################################################################
// Allumer une lumière
// Turn a light on

// 8 - pin
// 4978 - note
// 1000 - duration = 1 second
#include "MeOrion.h"
MeRGBLed led(PORT_3);


uint8_t red	= 64 * (1 + sin(t / 2.0 + j / 4.0) );
uint8_t green = 64 * (1 + sin(t / 1.0 + f / 9.0 + 2.1) );
uint8_t blue = 64 * (1 + sin(t / 3.0 + k / 14.0 + 4.2) );

led.setColorAt(t, red, green, blue);
led.show();
// #################################################################################################