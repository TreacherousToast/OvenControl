// When I tested this with the toaster oven, it was accurate to +-5C.
// It initially got to 10C greater than target temp (100C), but then stabilized between 105C and 95C.

#include <SPI.h>
#include "Adafruit_MAX31855.h"

// don't change these
#define MAXDO   3 // pins that the thermocouple amplifier connects to on the Arduino, if you need to reconnect it
#define MAXCS   4
#define MAXCLK  5

double currTime = 0.000;
bool started = false;

Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);

// change these
const double targetTime = 2.000; // in hours
const int targetTemp = 160; // in celsius
const int delayTime = 1000;

void setup() 
{
  Serial.begin(9600); // starting the MAX chip
  while (!Serial) delay(1);
  Serial.println("MAX31855 test");
  delay(500);
  
  pinMode(8,OUTPUT); // setting pin 8 as the relay control pin
}

void loop() 
{
  double c = thermocouple.readCelsius(); // reads thermocouple temp sent by the chip over SPI
  
  if (isnan(c)) 
  {
    Serial.println("Thermocouple error");
  } 
  else 
  {
     Serial.println(c);
  }
  
  if (c < targetTemp && currTime < targetTime) // basically saying if the temperature is less than the target temperature, turn on relay
  {
    digitalWrite(8,HIGH);
  }
  else // if the temperature is greater than the target temperature, turn off the relay
  {
    digitalWrite(8,LOW);
    started = true;
  }
  
  // timing stuff
  /* disabling this all now because the Arduino isn't very accurate at keeping time, so I don't want it to be thought of as accurate.
    if you want to enable it, just uncomment out this code.
    
  delay(delayTime);
  if (started == true)
  {
    currTime += (delayTime/3600000);
  }
  */
}
