#include <SDL3/SDL.h>
#include "geometry.h"
#include "config.h"
#include "bullet.h"
#include "character.h"

extern Character_t player;
extern Bullet_t bullets[BULLET_COUNT];

SDL_FPoint mouse;


int
main(void)
{
  SDL_Window   *window;
  SDL_Renderer *renderer;
  SDL_Event     event;
  SDL_bool      loop;

  Uint64 last_time, current_time = 0;
  float delta_time = 0;

  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED);

  for (loop = SDL_TRUE; loop; )
  {
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
	case SDL_EVENT_QUIT:
	{
	  loop = SDL_FALSE;
	  break;
	}
	case SDL_EVENT_KEY_DOWN:
	{
	  switch (event.key.keysym.sym)
	  {
	    case SDLK_ESCAPE:
	      loop = SDL_FALSE;
	      break;
	  }
	  break;
	}
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
	{
	  if (player.atackStatus == ATACK_STATUS_IDLE)
	    player.atackStatus = ATACK_STATUS_SHOT;
	  break;
	}
	case SDL_EVENT_MOUSE_BUTTON_UP:
	{
	  if (player.atackStatus == ATACK_STATUS_WAIT)
	    player.atackStatus = ATACK_STATUS_IDLE;
	  break;
	}
      }
    }


    /* update state */

    current_time = SDL_GetTicks();
    delta_time   = (current_time - last_time) / 1000.;
    last_time    = current_time;

    float cx = player.x + player.w / 2.;
    float cy = player.y + player.h / 2.;

    if (SDL_GetMouseFocus())
    {
      SDL_GetMouseState(&mouse.x, &mouse.y);
      player.angle = getAngleBetweenFPoints(
	(SDL_FPoint) { cx, cy }, (SDL_FPoint) { mouse.x, mouse.y });
    }

    if (player.atackStatus == ATACK_STATUS_SHOT)
    {
      Bullets_Fire(&player);
      player.atackStatus = ATACK_STATUS_WAIT;
    }

    Bullets_Update(delta_time);


    /* draw the screen */

    // clear screen
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // draw player
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, SDL_ALPHA_OPAQUE);
    //SDL_RenderRect(renderer, Character_GetRect(&player));
    SDL_RenderRect(renderer, &(SDL_FRect){ player.x, player.y, player.w, player.h });

                             // draw line from player to mouse cursor
    /*if (SDL_GetMouseFocus()) // but only if mouse cursor inside the window
    {
      SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
      SDL_RenderLine(renderer, cx, cy, mouse.x, mouse.y);
    }*/

    // draw player's view
    SDL_FPoint view = getFPointFromAngle(
      (SDL_FPoint) { cx, cy }, player.angle, PLAYER_VIEW);
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderLine(renderer, cx, cy, view.x, view.y);

    Bullets_Render(renderer);

    // draw from buffer to screen
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
