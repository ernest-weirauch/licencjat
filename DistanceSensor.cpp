#include "DistanceSensor.h"


DistanceSensor::DistanceSensor() {
}

DistanceSensor::DistanceSensor(int pinEcho, int pinTrig): Sensor() { // :Sensor - wywolanie kosnstruktora klasy bazowej z parametrami (wlasciwie to bez parametrow)
  this->pinEcho = pinEcho;
  this->pinTrig = pinTrig;

  pinMode(pinEcho, INPUT);
  pinMode(pinTrig, OUTPUT);

  this->maxDistance = 100;
  this->safeDistance = 10;

}

long DistanceSensor::doReading() {
  if(state){
    digitalWrite(pinTrig, LOW); // Ustawiamy TRIG w stan niski na 2us
    delayMicroseconds(2);

    digitalWrite(pinTrig, HIGH); // Ustawiamy TRIG w stan wysoki na 10us
    delayMicroseconds(10);

    digitalWrite(pinTrig, LOW); // Ustawiamy TRIG w stan niski - rozpoczynamy pomiar


    echoTime = pulseIn(pinEcho, HIGH, 58*maxDistance); // Odczytujamy czas trwania stanu wysokiego na pinie ECHO

    reading = echoTime / 58; // Obliczamy odległość

    return reading;
  } else return -1;
}

triState DistanceSensor::isObstacle(){ //czy jest przeszkoda
  if(reading == 0 || reading>=maxDistance) return Undefinied;
  else if(reading <= safeDistance) return True;
  return False;
}

unsigned short DistanceSensor::getMaxDistance(){
  return maxDistance;
}

unsigned short DistanceSensor::getSafeDistance(){
  return safeDistance;
}

void DistanceSensor::setSafeDistance(unsigned short safeDistance){
  this->safeDistance = safeDistance;
}

void DistanceSensor::setMaxDistance(unsigned short maxDistance){
  this->maxDistance = maxDistance;
}
