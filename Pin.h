#ifndef Pin_h
#define Pin_h

#include "Arduino.h"
#include "Constants.h"

class Pin{
protected:
    int pin;
    static bool usedPins[20]; //?
    /*0-13, A0-15 ... A5-20*/
    bool error;
    int state;
    Type type;
    const int analogPins[6];
    const int pwmPins[6];
    
public:
    Pin();
    Pin(int pin);
    bool isError();
    bool* getUsedPins();
    int toInt();
    void setState(bool);
    void setState(int);
    int getState();
    void setType(Type);
    Type getType();
};

#endif
