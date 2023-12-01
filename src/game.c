#include "game.h"

extern Character_t player;
extern Bullet_t bullets[BULLET_COUNT];

Game_t game;
SDL_FPoint mouse;

void
Game_Init(void)
{
  if (SDL_Init(SDL_INIT_VIDEO))
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init(). %s", SDL_GetError());
    Game_Quit();
    exit(1);
  }
  
  if (!(game.window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0)))
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow(). %s", SDL_GetError());
    Game_Quit();
    exit(1);
  }

  if (!(game.renderer = SDL_CreateRenderer(game.window, NULL, SDL_RENDERER_ACCELERATED)))
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateRenderer(). %s", SDL_GetError());
    SDL_DestroyWindow(game.window);
    Game_Quit();
    exit(1);
  }

  game.loop = SDL_TRUE;
}

void
Game_Quit(void)
{
  if (game.renderer)
    SDL_DestroyRenderer(game.renderer);

  if (game.window)
    SDL_DestroyWindow(game.window);

  if (SDL_WasInit(SDL_INIT_VIDEO))
    SDL_Quit();
}

SDL_bool
Game_Loop(void)
{
  game.deltatime = GetDeltaTime();
  return game.loop;
}

void
Game_Events()
{
  while (SDL_PollEvent(&game.event))
  {
    switch (game.event.type)
    {
      case SDL_EVENT_QUIT:
      {
	game.loop = SDL_FALSE;
	break;
      }
      case SDL_EVENT_KEY_DOWN:
      {
	switch (game.event.key.keysym.sym)
	{
	  case SDLK_ESCAPE:
	    game.loop = SDL_FALSE;
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
}

void
Game_Update(void)
{
  float cx = player.x + player.w / 2.;
  float cy = player.y + player.h / 2.;

  if (SDL_GetMouseFocus())
  {
    SDL_GetMouseState(&mouse.x, &mouse.y);
    player.angle = GetAngleBetweenFPoints(
      &(SDL_FPoint) { cx, cy },
      &(SDL_FPoint) { mouse.x, mouse.y }
    );
  }

  if (player.atackStatus == ATACK_STATUS_SHOT)
  {
    Bullets_Fire(&player);
    player.atackStatus = ATACK_STATUS_WAIT;
  }

  Bullets_Update(game.deltatime);
}

void
Game_Render(void)
{
  float cx = player.x + player.w / 2.;
  float cy = player.y + player.h / 2.;

  // clear screen
  SDL_SetRenderDrawColor(game.renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(game.renderer);

  // draw player
  SDL_SetRenderDrawColor(game.renderer, 0x00, 0x00, 0xFF, SDL_ALPHA_OPAQUE);
  SDL_FRect rect = Character_GetRect(&player);
  SDL_RenderRect(game.renderer, &rect);

  // draw player's view
  SDL_FPoint view = GetFPointFromAngle(
    &(SDL_FPoint) { cx, cy },
    player.angle,
    PLAYER_VIEW
  );
  SDL_SetRenderDrawColor(game.renderer, 0x00, 0xFF, 0x00, SDL_ALPHA_OPAQUE);
  SDL_RenderLine(game.renderer, cx, cy, view.x, view.y);

  Bullets_Render(game.renderer);

  // draw from buffer to screen
  SDL_RenderPresent(game.renderer);
}
