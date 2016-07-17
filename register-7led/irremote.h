#include <avr/interrupt.h>
#include <avr/io.h>

enum buttons
{
repeat    = 1,
ch_minus  = 41565,
ch        = 25245,
ch_plus   = 57885,
prev      = 8925,
next      = 765,
play      = 49725,
vol_minus = 57375,
vol_plus  = 43095,
eq        = 36975,
ch0   = 26775,
ch1xx = 39015,
ch2xx = 45135,
ch1   = 12495,
ch2   = 6375,
ch3   = 31365,
ch4   = 4335,
ch5   = 14535,
ch6   = 23205,
ch7   = 17085,
ch8   = 19125,
ch9   = 21165
};

void IRRemoteInit()
{
  TCCR1A = 0x00;
  TCCR1B = 0x03;
}

bool OutOfInterval(int IRPin, bool value, int min, int max)
{
  TCNT1 = 0;
  while(digitalRead(IRPin) == value);
  return TCNT1 < min || TCNT1 > max;
}

int ReadValueCore(int IRPin)
{
  int res = 0;

  for(byte i = 0; i < 16; i++)
  {
    if(OutOfInterval(IRPin, LOW, 120, 160) ||
       OutOfInterval(IRPin, HIGH, 120, 440) ||
       TCNT1 > 160 && TCNT1 < 400)
      return 0;

    res <<= 1;
    res |= TCNT1 > 256;
  }

  return res;
}

buttons ReadValue(int IRPin)
{
  for(;;)
  {
    while(digitalRead(IRPin) == HIGH);

    if(OutOfInterval(IRPin, LOW, 2200, 2300))
      continue;

    TCNT1 = 0;
    while(digitalRead(IRPin) == HIGH);
    if(TCNT1 > 530 && TCNT1 < 590)
    {
      if(OutOfInterval(IRPin, LOW, 120, 160))
        continue;
      return repeat;
    }
    
    if(TCNT1 < 1050 || TCNT1 > 1200 ||
       ReadValueCore(IRPin) != 255)
      continue;
  
    int res = ReadValueCore(IRPin);

    if(res != 0)
      return (buttons)res;
  }
}