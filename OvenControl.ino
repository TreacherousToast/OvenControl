#include <SPI.h>
#include "Adafruit_MAX31855.h"

// don't change these
#define MAXDO   3
#define MAXCS   4
#define MAXCLK  5

double currTime = 0.000;
bool started = false;

Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);

// change these
const double targetTime = 2.000; // in hours
const int targetTemp = 30; // in celsius
const int delayTime = 1000;

void setup() 
{
  Serial.begin(9600); // starting the MAX chip
  while (!Serial) delay(1);
  Serial.println("MAX31855 test");
  delay(500);
  
  pinMode(8,OUTPUT);
}

void loop() 
{
  double c = thermocouple.readCelsius();
  
  if (isnan(c)) 
  {
    Serial.println("Thermocouple error");
  } 
  else 
  {
     Serial.println(c);
  }
  
  if (c < targetTemp && currTime < targetTime)
  {
    digitalWrite(8,HIGH);
  }
  else
  {
    digitalWrite(8,LOW);
    started = true;
  }
  delay(delayTime);
  if (started == true)
  {
    currTime += (delayTime/3600000);
  }
}
