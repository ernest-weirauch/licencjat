#include "LedDiode.h"

LedDiode::LedDiode(){
  this->pin = 13; //w przypadku braku argumentu ustawia na wewnętrzną diodę
}

LedDiode::LedDiode(int pin){
  this->pin = pin;
  
  pinMode(pin, OUTPUT);
  setState(off);
    
}

void LedDiode::setState(State state){
  this->state = state;
  if(state==on) digitalWrite(pin, HIGH);
  else digitalWrite(pin, LOW);
}

void LedDiode::setState(bool state){
  if(state) setState(on);
  else setState(off);
}

State LedDiode::getState(){
  return state;
}

int LedDiode::getBrightness(){
  return brightness;
}

bool LedDiode::setBrightness(int brightness){
  if(brightness>=0 && brightness<=255){
      this->brightness = brightness;  
      analogWrite(pin, this->brightness);  
      return true;
  }
  else return false;
  
}




