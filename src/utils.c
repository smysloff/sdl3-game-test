#include "utils.h"

float
GetDeltaTime(void)
{
  static Uint64 lasttime;
  static Uint64 ticks;
  float deltatime;

  ticks = SDL_GetTicks();
  deltatime = (ticks - lasttime) / 1000.;
  lasttime = ticks;

  return deltatime;
}
