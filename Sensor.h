#ifndef Sensor_h
#define Sensor_h

#include "Arduino.h"
#include "Constants.h"

class Sensor { //this should be abstract
protected:
  int reading;
  State state;
public:
  Sensor();
  int getReading();
  
  //void setState(State);
  void setState(State);
  State getState();
};

#endif



