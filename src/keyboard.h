#pragma once

#include <SDL3/SDL.h>

typedef struct Keyboard_s
{
  SDL_bool escape;
  SDL_bool up, left, down, right;
  SDL_bool w, a, s, d;
} Keyboard_t;

void
Keyboard_KeyDown_Handler(SDL_KeyboardEvent *event);

void
Keyboard_KeyUp_Handler(SDL_KeyboardEvent *event);
