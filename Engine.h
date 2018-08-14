#ifndef Engine_h
#define Engine_h

#include "Arduino.h"
#include "Constants.h"


class Engine{
protected:    
    bool state;
    Direction direction;
    int speed;
    int logicPin1, logicPin2;
    int speedPin;
public:
    Engine();
    Engine(int, int, int);
   
    //bool isOn();
    //void setState(bool);
    //int getSpeed();
    void setSpeed(int);
    Direction getDirection();
    void setDirection(Direction);
    void stop();
    void sendToEngine();
};

#endif
