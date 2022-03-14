#include <Servo.h>
#include <TM1637.h>
#define NORMALIZE_P 128

const uint8_t pressurePin = A0;
const uint8_t hw_clkPin = 3;
const uint8_t dtPin = 2;
const uint8_t triggerPin = 1;
const uint8_t servoPin = 7;
const uint8_t clkPin = 9;
const uint8_t dioPin = 8;
const uint8_t ledPin = 5;

Servo myServo;
TM1637 tm(clkPin, dioPin);

volatile uint8_t soglia = 108;
volatile bool actived = false;
volatile bool LeftRight;
volatile uint8_t rotation;

uint8_t i=0;
uint32_t pressure = 0;
uint8_t cachedPressure = 0;

void startStop(){
  if(digitalRead(triggerPin)==HIGH){
    actived = !actived;
  }
}

void dec_increase(){ 
  uint8_t value = digitalRead(hw_clkPin);
  if (value != rotation){
     if (digitalRead(dtPin) != value) {
       if (soglia != 255) soglia++;
       LeftRight = true;
     } else { //Counterclockwise
       LeftRight = false;
       if (soglia != 1) soglia--;
     }
  }
  rotation = value;
}

void displayNumber(int num){   
    tm.display(3, num % 10);   
    tm.display(2, num / 10 % 10);   
    tm.display(1, num / 100 % 10);   
    tm.display(0, num / 1000 % 10);
}

void setup() {
  myServo.attach(servoPin);
  actived = false;
  pinMode(pressurePin, INPUT);
  pinMode(triggerPin, INPUT_PULLUP);
  pinMode(hw_clkPin, INPUT_PULLUP);
  pinMode(dtPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  LeftRight = true;
  rotation = digitalRead(hw_clkPin);
  attachInterrupt(digitalPinToInterrupt(triggerPin), startStop, CHANGE);
  attachInterrupt(digitalPinToInterrupt(hw_clkPin), dec_increase, CHANGE);
  myServo.write(0);
  tm.init();
  tm.set(0);
  tm.point(0);
  displayNumber(0);
  
}

void loop() {
  if( i<NORMALIZE_P ){
    pressure+=analogRead(pressurePin);
    i++;
  } else {
    i=0;
  }

  if(i==0){
    pressure=pressure/NORMALIZE_P;
    if(pressure>=soglia){
      actived = false;
    }
    cachedPressure = pressure;
    pressure = 0;
  }

  if(i%8==0){
    if(actived){
      digitalWrite(ledPin, HIGH);
      displayNumber(cachedPressure);
      myServo.write(90);
    } else {
      digitalWrite(ledPin, LOW);
      displayNumber(soglia);
      myServo.write(0);
    }
  }
}
