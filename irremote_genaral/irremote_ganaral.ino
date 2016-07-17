#include <avr/interrupt.h>

void setup()
{
  TCCR1A = 0x00;
  TCCR1B = 0x03;
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(2), onChanged, CHANGE);
}

void onChanged()
{
  auto time = TCNT1;
  TCNT1 = 0;
  auto val = digitalRead(2);

  Serial.print(time);
  Serial.print("\t");
  Serial.println(!val);
  Serial.print("0\t");
  Serial.println(val);
}

void loop()
{
}

