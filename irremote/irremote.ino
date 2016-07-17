#include "irremote.h"

volatile buttons lastButton = none, lastRepeatButton;
volatile bool repeatPressed, stopped;
const int pinIR = 2;
const int pinPlus = 6;
const int pinMinus = 7;

void setup()
{
  //Serial.begin(115200);
  pinMode(pinPlus, OUTPUT);
  pinMode(pinMinus, OUTPUT);
  pinMode(A0, OUTPUT);
  analogWrite(A0, 1023);
  IR::Initialize();
  attachInterrupt(digitalPinToInterrupt(pinIR), onChanged, CHANGE);
}

void onChanged()
{
  auto b = IR::onChanged(digitalRead(pinIR));

  repeatPressed = false;
  switch(b)
  {
    case none: return;
    case invalid: lastButton = none; break;
    case repeat:
      b = lastRepeatButton;
      lastButton = b;
      repeatPressed = true;
      break;
    default:
      lastButton = b;
      lastRepeatButton = b;
      break;
  }

  switch(b)
  {
    case vol_plus:
      digitalWrite(pinPlus, HIGH);
      digitalWrite(pinMinus, LOW);
      stopped = false;
      //Serial.println("+");
      break;
    case vol_minus:
      digitalWrite(pinPlus, LOW);
      digitalWrite(pinMinus, HIGH);
      stopped = false;
      //Serial.println("-");
      break;
    default:
    Serial.println(b);
      digitalWrite(pinPlus, HIGH);
      digitalWrite(pinMinus, HIGH);
      //Serial.println("?");
      break;
  }
}

void loop()
{
  delay(70);
  if(lastButton == none)
  {
    if(!stopped)
    {
      digitalWrite(pinPlus, HIGH);
      digitalWrite(pinMinus, HIGH);
      //Serial.println("stop");
      stopped = true;
    }
  }
  else
    if(repeatPressed)
      repeatPressed = false;
    else
      lastButton = none;
}

