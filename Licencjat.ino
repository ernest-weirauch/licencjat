#include <Timers.h> //wywoływanie funkcji w podanym interwale czasowym
#include <XBOXRECV.h> //obsługa ShieldaUSB oraz urządzeń podłączonych do portu USB hosta
#include "Constants.h" //Zawiera stałe
#include "Engine.h"
#include "BistableSwitch.h"
#include "LedDiode.h"
#include "Sensor.h"
#include "DistanceSensor.h"

// Zastapienie polecenia Serial.println(), poleceniem: Serial<<  -  WYPISYWANIE NA EKRAN
template<class T>  Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
} //Operator <<
#define endl "\n"


#define JOY_DEADZONE 0.25 //martwa strefa 0.5 = 50% itd. - pozycja joysticka, od ktorej zmienia sie stan na inny niz 0
#define JOY_MIN -32768 //minimalny odczyt pozycji joysticka
#define JOY_MAX 32767 //max /\


// TU POWINNY BYĆ DEKLARACJE FUNKCJI ALE W ARDUINO IDE
// FUNKCJE DZIAŁAJA BEZ DEKLARACJI NA POCZĄTKU KODU - W PRZECIWIEŃSTWIE DO NORMALNEGO C++


//-------- Zmienne GLOBALNE
unsigned int reactsPerSec = 0;



//Tworzenie obiektów (deklaracje klas wewnątrz plików nagłówkowych)
USB Usb;
XBOXRECV XboxRCV(&Usb);
Engine leftEngine(pin1_leftMotor, pin2_leftMotor, pinSpeed_leftMotor);
Engine rightEngine(pin1_rightMotor, pin2_rightMotor, pinSpeed_rightMotor);
LedDiode frontLights(pin_frontLights);
BistableSwitch switch_frontLights;



struct ControllerState {
  int joyLX, joyLY, joyRX, joyRY;
  int trigL, trigR;
  bool btnA, btnB, btnX, btnY;
  bool btnBack, btnStart;
  bool btnR1, btnL1;
  bool btnR3, btnL3;
  bool btnLeft, btnRight, btnUp, btnDown;
} pad, lastPadState;


TimerPool timer(2); //Liczba timerow - funkcji wywolywanych w stalych odstepach czasu
void setup() {
  Serial.begin(115200); //komunikacja przez konsolę - głównie debugowanie

  while (Usb.Init() == -1) {
    Serial << "!!! Oczekiwanie na polaczenie z shieldem USB..." << endl;
    delay(300);
  }
  Serial << "#### Polaczono z shieldem USB" << endl;

  //podłączenie timerów
  timer.connect(0, 5, react); //id, time(ms), func
  timer.connect(1, 1000, printStatistics);


  delay(100); //odczekaj chwilę dla stabilności
  Serial.println("### Wykonano setup()");
}

void loop() {
  timer.update(); //aktualizacja timera
}

void react() {   //reakcja na stan kotrolera
  readController(); //wczytaj stan przyciskow i joystickow na kontrolerze i zapisz w strukturze


  //Jazda przod/tyl
  int tr = map(pad.trigR, 0, 255, 0, -255);// [-255,0]
  int tl = pad.trigL; //[0, 255]
  int sum = tl + tr; //sum[-255,255]

  if (sum != 0) { //steruj triggerami jesli ktorys nacisniety
    if (sum > 0) {
      setEngines(FORWARD, sum);
    } else if (sum < 0) {
      setEngines(BACKWARD, map(sum, 0, -255, 0, 255));
    } else {
      setEngines(STAND);
    }
  } else { //steruj joyem LY
    int ly = pad.joyLY;
    if (ly > 0) {
      setEngines(FORWARD, map(abs(ly), JOY_MAX * JOY_DEADZONE, JOY_MAX, 0, 255));
    } else if (ly < 0) {
      setEngines(BACKWARD, map(abs(ly), JOY_MIN * JOY_DEADZONE, JOY_MAX, 0, 255));
    } else {
      setEngines(STAND);
    }
  
   }


  //skrety
  int rx = pad.joyRX;
  int speed = map(abs(rx), JOY_MIN, JOY_MAX, 0, 255);
  if (rx > 0) {
    rightEngine.setDirection(BACKWARD);
    rightEngine.setSpeed(speed);
    leftEngine.setDirection(FORWARD);
    leftEngine.setSpeed(speed);
  } else if (rx < 0) {
    rightEngine.setDirection(FORWARD);
    rightEngine.setSpeed(speed);
    leftEngine.setDirection(BACKWARD);
    leftEngine.setSpeed(speed);
  }

  //światła przednie
  switch_frontLights.update(pad.btnY);
  if(switch_frontLights.getState()==on)
    frontLights.setState(on);
  else
    frontLights.setState(off);
    
  


  reactsPerSec++;
} //loop()


  void readController() {
    Usb.Task();

    if (!(XboxRCV.Xbox360Connected[0])) {
      Serial << "!!! Brak polaczenia radiowego z kontrolerem" << endl;
      delay(33);
      return; //wyjdz z funkcji
    }

    pad.trigL = XboxRCV.getButtonPress(L2, 0); //0-255
    pad.trigR = XboxRCV.getButtonPress(R2, 0);

    // wczytanie stanu joystickow
    pad.joyLX = XboxRCV.getAnalogHat(LeftHatX, 0);
    pad.joyRX = XboxRCV.getAnalogHat(RightHatX, 0);
    pad.joyLY = XboxRCV.getAnalogHat(LeftHatY, 0);
    pad.joyRY = XboxRCV.getAnalogHat(RightHatY, 0);

    pad.btnA = XboxRCV.getButtonPress(A, 0);   // jest jeszcze wariant getButtonClick
    pad.btnB = XboxRCV.getButtonPress(B, 0);
    pad.btnX = XboxRCV.getButtonPress(X, 0);
    pad.btnY = XboxRCV.getButtonPress(Y, 0);

    pad.btnR1 = XboxRCV.getButtonPress(R1, 0);
    pad.btnL1 = XboxRCV.getButtonPress(L1, 0);

    pad.btnLeft = XboxRCV.getButtonPress(LEFT, 0);
    pad.btnRight = XboxRCV.getButtonPress(RIGHT, 0);
    pad.btnUp = XboxRCV.getButtonPress(UP, 0);
    pad.btnDown = XboxRCV.getButtonPress(DOWN, 0);

    pad.btnR3 = XboxRCV.getButtonPress(R3, 0);
    pad.btnL3 = XboxRCV.getButtonPress(L3, 0);

    pad.btnBack = XboxRCV.getButtonPress(BACK, 0);
    pad.btnStart = XboxRCV.getButtonPress(START, 0);


    //poprawki na martwa strefe TYLKO DLA LY I RX!

    if (pad.joyLY <= -32768) pad.joyLY = -32767;
    if (pad.joyRX <= -32768) pad.joyRX = -32767;
    int dly = abs(pad.joyLY);
    int drx = abs(pad.joyRX);
    if (dly < JOY_MAX * JOY_DEADZONE) pad.joyLY = 0;
    if (drx < JOY_MAX * JOY_DEADZONE) pad.joyRX = 0;


    lastPadState = pad;
  }

  void setEngines(Direction direction) {
    if (direction = STAND) {
      leftEngine.stop();
      rightEngine.stop();
    }
  }

  void setEngines(Direction direction, int speed) {
    leftEngine.setDirection(direction);
    rightEngine.setDirection(direction);
    leftEngine.setSpeed(speed);
    rightEngine.setSpeed(speed);
  }

  void printStatistics(){
    Serial<<"# reacts/s: "<<reactsPerSec<<endl;
    
    reactsPerSec=0;
  }


