#include "Pin.h"

bool Pin::usedPins[20]={false};
const int Pin::analogPins[6]={A0, A1, A2, A3, A4, A5};
const int Pin::pwmPins[6]={3,5,6,9,10,11}

Pin::Pin(){ /*error*/}

Pin::Pin(int pin){
    if(usedPins[pin]==true){
        //error
    } else{
        usedPins[pin]=true;
        this->pin = pin;
    }
    
    for(int i=0;i<6;i++){
      if(pin==analogPins[i]) type=ANALOG;
      if(pin==pwmPins[i]) type=PWM;   
    }

}

bool Pin::isError(){
    return error;
}

bool* Pin::getUsedPins(){
    return usedPins;
}

int Pin::toInt(){
    return pin;
}

void Pin::setState(bool state){
    this.state = state;
}

void Pin::setState(int state){
  if(type==DIGITAL){
    if(state!=0 && state!=1){ //error } 
    else this->state=state;
  } else if(type==ANALOG){
    if(state<0 || state>1023){ //error }
    else this->state = state;
  } else{
    //error
  }
}

int Pin::getState(){
  return state;
}

void Pin::setType(Type type){
  this->type = type;
}
  
Type Pin::getType(){
  return type;
}
