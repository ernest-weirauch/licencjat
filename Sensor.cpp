#include "sensor.h"

Sensor::Sensor(){
  reading=0;
  setState(on);
}

int Sensor::getReading(){
  return reading;
}

void Sensor::setState(State state){
  this->state = state;
}

State Sensor::getState(){
  return state;
}
