#ifndef Constants_h
#define Constants_h

#include "Arduino.h"

//--------- Stałe pinów (dla porządku)
typedef enum ePin {
  pin1_leftMotor = 7,
  pin2_leftMotor = 8,
  pinSpeed_leftMotor = 5,
  pin1_rightMotor = 2,
  pin2_rightMotor = 4,
  pinSpeed_rightMotor = 3,
  pin_frontLights = 6,
  pin_encoderLeft = 2
  
}; // \/uzyte ale nie sa tu wpisane
//cala magistrala SPI: 10, 11, 12, 13


typedef enum State{
  off=0, on=1
};

typedef enum TriState {
  False = 0,
  True = 1,
  Undefinied
} triState;

typedef enum{
  FORWARD, BACKWARD, STAND
}Direction;

typedef enum{
  DIGITAL, ANALOG
}Type;

#endif



