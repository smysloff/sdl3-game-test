#pragma once

#include <stdlib.h>
#include <SDL3/SDL.h>
#include "keyboard.h"
#include "mouse.h"
#include "config.h"
#include "utils.h"
#include "geometry.h"
#include "bullet.h"
#include "character.h"

typedef struct Game_s
{
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;
  SDL_bool loop;
  float deltatime;
} Game_t;

void
Game_Init(void);

void
Game_Quit(void);

SDL_bool
Game_Loop(void);

void
Game_Events(void);

void
Game_Update(void);

void
Game_Render(void);
