#ifndef LightSensor_h
#define LightSensor_h

#include "Arduino.h"
#include "Sensor.h"

class LightSensor: public Sensor {
private:
  int pin;
public:
  LightSensor();
  LightSensor(int); //pin
  int doReading();
 
};

#endif



