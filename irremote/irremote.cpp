#include "irremote.h"

unsigned char state = 255;
unsigned int val;

void IR::Initialize()
{
  TCCR1A = 0x00;
  TCCR1B = 0x03;
}

buttons IR::onChanged(bool rising)
{
  auto time = TCNT1;
  TCNT1 = 0;

  return (buttons)(rising ? onRising(time) : onFalling(time));
}
  
unsigned int IR::onRising(int time)
{
  switch(state)
  {
  case 255:
    break;
    
  case 0:
    state = time < 2200 || time > 2400 ? 255 : 1;
    break;
    
  case 2:
    state = 255;
    if(time >= 100 && time <= 180)
      return 2;
    break;
    
  case 69:
    if(time < 2200 || time > 2600)
      state = 255;
    else
      state++;
    break;

  default:
    if(state >= 3 && state <= 71)
      if(time < 100 || time > 180)
        state = 255;
      else
        if(state == 71)
        {
          state = 255;
          return val;
        }
        else
          state++;
    else
      state = 255;
    break;
  }

  return state == 255 ? 1 : 0;
}

unsigned int IR::onFalling(int time)
{
  switch(state)
  {
    case 1:
      if(time > 1100 && time < 1200)
      {
        val = 0;
        state = 3;
      }
      else
        state = time < 530 || time > 590 ? 255 : 2;
      break;
      
    case 68:
      if(time < 9800 || time > 10000)
        state = 255;
      else
        state++;
      break;
      
    case 70:
      if(time < 530 || time > 580)
        state = 255;
      else
        state++;
      break;
        
    default:
      if(state >= 4 && state <= 66 &&
         (time >= 100 && time <= 180 ||
          time >= 400 && time <= 460))
      {
        val <<= 1;
        val |= time > 256;

        if(state == 34)
          if(val == 255)
          {
            val = 0;
            state++;
          }
          else
            state = 255;
        else
            state++;
      }
      else
        state = 255;
      break;
  }

  if(state == 255 &&
    (time < 0 || time > 500))
        state = 0;

  return state == 255 ? 1 : 0;
}
