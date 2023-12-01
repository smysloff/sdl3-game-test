#include "game.h"

int
main(void)
{
  Game_Init();
  while (Game_Loop())
  {
    Game_Events();
    Game_Update();
    Game_Render();
  }
  Game_Quit();
}
