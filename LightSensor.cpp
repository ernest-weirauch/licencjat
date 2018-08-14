#include "LightSensor.h"

LightSensor::LightSensor(){
}

LightSensor::LightSensor(int pin):Sensor(){
  this->pin = pin;

  pinMode( pin, INPUT );

}

int LightSensor::doReading(){
  if(state){
    reading = analogRead(pin);
  
    return reading;
  } else return -1;
  
}



