#ifndef LedDiode_h
#define LedDiode_h

#include "Arduino.h"
#include "Constants.h"


class LedDiode {
protected:
  int pin;
  State state;
  int brightness;
public:
  LedDiode();
  LedDiode(int); //pin
  void setState(State); //state
  void setState(bool);
  State getState();
  int getBrightness();
  bool setBrightness(int);
  
};

#endif



