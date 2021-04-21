
#include <Wire.h>
#include "IOExpander.h"
#include <Arduino.h>


//define ioExpander address
#define ioExpander01 0x20
#define ioExpander23 0x21
#define ioExpander45 0x22
#define ioExpander67 0x23
#define ioExpanderColor 0x24
#define ioExpanderBig 0x25
#define ioExpanderMotors 0x26


//define arduino pins
#define i2c0Int 18
#define i2c1Int 21
#define i2c2Int 24
#define i2c3Int 27
#define i2c4Int 30
#define LEDBrightness 34
#define MotorSpeed1 35
#define MotorSpeed2 36
#define MotorStby 37
#define OLEDReset 38
//#define byte uint8_t


//Array of Wire Object
TwoWire myWire[6] {{&sercom0, 17, 16}, {&sercom1, 20, 19}, {&sercom2, 23, 22}, {&sercom3, 26, 25}, {&sercom4, 29, 28}, {&sercom5, 32, 31}};



//set InterruptServiceRoutine Variables
volatile bool Interrupt01 = false;
volatile bool Interrupt23 = false;
volatile bool Interrupt45 = false;
volatile bool Interrupt67 = false;
volatile bool InterruptBigShort = false;



IOExpander IOCh01(ioExpander01, myWire[0]);
IOExpander IOCh23(ioExpander23, myWire[1]);
IOExpander IOCh45(ioExpander45, myWire[2]);
IOExpander IOCh67(ioExpander67,  myWire[3]);
IOExpander IOChColor(ioExpanderColor, myWire[4]);
IOExpander IOChBig(ioExpanderBig, myWire[4]);
IOExpander IOChMotors(ioExpanderMotors, myWire[5]);



void setup() {
    //Start Serial Port
  Serial.begin(9600);

  //set hardware pinModes
  pinMode (LEDBrightness, OUTPUT);
  pinMode (MotorStby, OUTPUT);
  pinMode (MotorSpeed1, OUTPUT);
  pinMode (MotorSpeed2, OUTPUT);

  pinMode(i2c0Int, INPUT);
  pinMode(i2c1Int, INPUT);
  pinMode(i2c2Int, INPUT);
  pinMode(i2c3Int, INPUT);
  pinMode(i2c4Int, INPUT);


  //Set hardware outputs
  digitalWrite(LEDBrightness, HIGH);
  digitalWrite(MotorStby, HIGH);
  digitalWrite(MotorSpeed1, HIGH);
  digitalWrite(MotorSpeed2, HIGH);


  //set ISR
  attachInterrupt(i2c0Int, ISRChan01, CHANGE);
  attachInterrupt(i2c1Int, ISRChan23, CHANGE);
  attachInterrupt(i2c2Int, ISRChan45, CHANGE);
  attachInterrupt(i2c3Int, ISRChan67, CHANGE);
  attachInterrupt(i2c4Int, ISRChanBig, CHANGE);


  // start I2C busses
  IOCh01.StartWire();
  IOCh23.StartWire();
  IOCh45.StartWire();
  IOCh67.StartWire();
  IOChBig.StartWire();
  //IOChColor.StartWire();
  IOChMotors.StartWire();


  //setup i2c busses IOExpanderSetup(Port0(Normally LED), Port1(NormallyButtons), Invert) Set LOW for OUTPUT, HGIH for INPUT
  IOCh01.IOExpanderSetup(0x00, 0xFF, 0xFF);
  IOCh23.IOExpanderSetup(0x00, 0xFF, 0xFF);
  IOCh45.IOExpanderSetup(0x00, 0xFF, 0xFF);
  IOCh67.IOExpanderSetup(0x00, 0xFF, 0xFF);
  IOChBig.IOExpanderSetup(0x00, 0xFF, 0xFF);
  IOChColor.IOExpanderSetup(0x00, 0x00, 0x00);
  IOChMotors.IOExpanderSetup(0x00, 0x00, 0x00);

  // TURN ON ALL LED'S
  //WriteIOExpander(port0(Normally LED), port1(NormallyButtons) High is on Low is off
  IOCh01.WriteIOExpander(0xFF, 0x00);
  IOCh23.WriteIOExpander(0xFF, 0x00);
  IOCh45.WriteIOExpander(0xFF, 0x00);
  IOCh67.WriteIOExpander(0xFF, 0x00);
  IOChBig.WriteIOExpander(0xFF, 0x00);
  IOChColor.WriteIOExpander(0xFF, 0xFF);
  IOChMotors.WriteIOExpander(0x00, 0x00); //make sure motors are set to 0

  
}
  


void loop() {
  // put your main code here, to run repeatedly:
  //checking for ISR Flags
  if (Interrupt01) {
    int buttons01 = IOCh01.ReadIOExpander();
    ChButtonPressed(buttons01);
    Interrupt01 = false;
  }

  if (Interrupt23) {
    int buttons23 = IOCh23.ReadIOExpander();
    ChButtonPressed(buttons23);
    Interrupt23 = false;
  }

  if (Interrupt45) {
    int buttons45 = IOCh45.ReadIOExpander();
    ChButtonPressed(buttons45);
    Interrupt45 = false;
  }

  if (Interrupt67) {
    int buttons67 = IOCh67.ReadIOExpander();
    ChButtonPressed(buttons67);
    Interrupt67 = false;
  }

  if (InterruptBigShort) {
    int buttonsBig = IOChBig.ReadIOExpander();
    BigButtonPressedShort(buttonsBig);
    InterruptBigShort = false;
  }


}

//----------------------function for channel button press-------------
void ChButtonPressed(int _buttons) {
  int buttons = _buttons;


  if (bitRead(buttons, 0)) { // AUTO2
    Serial.println("Button 0");
  }

  if (bitRead(buttons, 1)) { //REC2
    Serial.println("Button 1");
  }

  if (bitRead(buttons, 2)) { // MUTE 2
    Serial.println("Button 2");
  }

  if (bitRead(buttons, 3)) { // SOLO2
    Serial.println("Button 3");
  }

  if (bitRead(buttons, 4)) { //AUTO1
    Serial.println("Button 4");
  }

  if (bitRead(buttons, 5)) { //REC1
    Serial.println("Button 5");
  }

  if (bitRead(buttons, 6)) { //MUTE1
    Serial.println("Button 6");
  }

  if (bitRead(buttons, 7)) { //SOLO1
    Serial.println("Button 7");

  }
}

//-------------------"Big" Button Pressed-------------------
void BigButtonPressedShort(int _buttons) {
  //Top to bottom is Right to Left
  if (bitRead(_buttons, 0)) { // Channel Right
    Serial.println("Big Button 0");
  }

  if (bitRead(_buttons, 1)) { //Record Enable
    Serial.println("Big Button 1");
  }

  if (bitRead(_buttons, 2)) { // Play
    Serial.println("Big Button 2");
  }

  if (bitRead(_buttons, 3)) { // Stop
    Serial.println("Big Button 3");
  }

  if (bitRead(_buttons, 4)) { //Go To End
    Serial.println("Big Button 4");
  }

  if (bitRead(_buttons, 5)) { //Return To Zero
    Serial.println("Big Button 5");
  }

  if (bitRead(_buttons, 6)) { //FLIP
    Serial.println("Big Button 6");
  }

  if (bitRead(_buttons, 7)) { //Channel Left
    Serial.println("big Button 7");

  }
}



//--------------------INTERRUPT SERVICE ROUTINES-------------

void ISRChan01() {
  Interrupt01 = true;
}

void ISRChan23() {
  Interrupt23 = true;
}

void ISRChan45() {
  Interrupt45 = true;
}

void ISRChan67() {
  Interrupt67 = true;
}

void ISRChanBig() {
  InterruptBigShort = true;

}
