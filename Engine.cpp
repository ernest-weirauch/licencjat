#include "Engine.h"

Engine::Engine(){}

Engine::Engine(int logicPin1, int logicPin2, int speedPin){
  this->logicPin1 = logicPin1;
  this->logicPin2 = logicPin2;
  this->speedPin = speedPin;
  
  pinMode(logicPin1, OUTPUT);
  pinMode(logicPin2, OUTPUT);
  pinMode(speedPin, OUTPUT);
  
  digitalWrite(speedPin, LOW);
  digitalWrite(logicPin1, LOW);
  digitalWrite(logicPin2, LOW);
}
/*
bool Engine::isOn(){
  return state;
}

void Engine::setState(bool state){
  this->state = state;
}

int Engine::getSpeed(){
  return speed;
}
*/
void Engine::setSpeed(int speed){
  if(speed<0){
    //error
    speed=0; 
  } 
  if(speed>255){
    //error
    speed=225;
  }  
  if(speed==0) direction=STAND;  
    
  this->speed=speed;
  sendToEngine();
}

Direction Engine::getDirection(){
  return direction;
}

void Engine::setDirection(Direction direction){
    this->direction = direction;
    sendToEngine();
}

void Engine::sendToEngine(){
  if(direction==FORWARD){
    digitalWrite(logicPin1, LOW);
    digitalWrite(logicPin2, HIGH);
    
  } else if(direction==BACKWARD){
    digitalWrite(logicPin1, HIGH);
    digitalWrite(logicPin2, LOW);
    
  } else{
    digitalWrite(logicPin1, LOW);
    digitalWrite(logicPin2, HIGH);
  }
  
  analogWrite(speedPin, speed);
}

void Engine::stop(){
  speed=0;
  direction=STAND;
  
  sendToEngine();
}
