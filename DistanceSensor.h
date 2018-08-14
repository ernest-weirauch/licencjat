#ifndef DistanceSensor_h
#define DistanceSensor_h

#include "Arduino.h"
#include "Sensor.h"
#include "Constants.h"

class DistanceSensor :  public Sensor {
  private:
    int pinEcho;
    int pinTrig;
    int maxDistance; //max mierzona odleglosc, po jej przekroczeniu odczyt ma wartoœæ maxDistance
    int safeDistance; //bezpieczna odleg³oœæ od przeszkody, je¿eli jest mniejsza - natrafiono na przeszkode
    long echoTime;

  public:
    DistanceSensor();
    DistanceSensor(int, int); //echo, trig
    long doReading();
    triState isObstacle(); //czy jest przeszkoda w polu zasiegu
    unsigned short getMaxDistance();
    unsigned short getSafeDistance();
    void setMaxDistance(unsigned short);
    void setSafeDistance(unsigned short);

};

#endif


