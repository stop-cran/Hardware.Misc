#include <avr/interrupt.h>

enum buttons
{
none      = 0,
invalid   = 1,
repeat    = 2,
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

class IR
{
public:
	static void Initialize();
  static buttons onChanged(bool rising);

private:
  static unsigned int onRising(int time);
  static unsigned int onFalling(int time);
};
