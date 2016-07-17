const int SER = 2;
const int CLOCK = 3;
const int LATCH = 4;

#include "irremote.h"

const int IRpin = 5;

void setup() {
  IRRemoteInit();
  // put your setup code here, to run once:
  pinMode(SER,OUTPUT);
  pinMode(CLOCK,OUTPUT);
  pinMode(LATCH,OUTPUT);
  Serial.begin(115200);
}

buttons lastValue, lastPressedValue;

void loop()
{
  int value = 0;
  auto newValue = ReadValue(IRpin);

  if(newValue == repeat)
    newValue = lastPressedValue;
  else
    lastPressedValue = newValue;

  switch(newValue)
  {
    case vol_plus:
      switch(lastValue)
      {
        case ch0: newValue = ch1; break;
        case ch1: newValue = ch2; break;
        case ch2: newValue = ch3; break;
        case ch3: newValue = ch4; break;
        case ch4: newValue = ch5; break;
        case ch5: newValue = ch6; break;
        case ch6: newValue = ch7; break;
        case ch7: newValue = ch8; break;
        case ch8: newValue = ch9; break;
        case ch9: newValue = ch0; break;
      }
      break;

    case vol_minus:
      switch(lastValue)
      {
        case ch0: newValue = ch9; break;
        case ch1: newValue = ch0; break;
        case ch2: newValue = ch1; break;
        case ch3: newValue = ch2; break;
        case ch4: newValue = ch3; break;
        case ch5: newValue = ch4; break;
        case ch6: newValue = ch5; break;
        case ch7: newValue = ch6; break;
        case ch8: newValue = ch7; break;
        case ch9: newValue = ch8; break;
      }
      break;
  }

  switch(newValue)
  {
    case ch0: lastValue = newValue; value = B1111110; break;
    case ch1: lastValue = newValue; value = B1001000; break;
    case ch2: lastValue = newValue; value = B0111101; break;
    case ch3: lastValue = newValue; value = B1101101; break;
    case ch4: lastValue = newValue; value = B1001011; break;
    case ch5: lastValue = newValue; value = B1100111; break;
    case ch6: lastValue = newValue; value = B1110111; break;
    case ch7: lastValue = newValue; value = B1001100; break;
    case ch8: lastValue = newValue; value = B1111111; break;
    case ch9: lastValue = newValue; value = B1101111; break;
  }
  Serial.println(value);
  digitalWrite(LATCH,LOW);
  shiftOut(SER,CLOCK,MSBFIRST,value);
  digitalWrite(LATCH,HIGH);
  delay(50);
}
