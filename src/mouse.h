#pragma once

#include <SDL3/SDL.h>

typedef struct Mouse_s
{
  float x, y;
  Uint8 left, middle, right, x1, x2;
} Mouse_t;

void
Mouse_ButtonDown_Handler(SDL_MouseButtonEvent *event);

void
Mouse_ButtonUp_Handler(SDL_MouseButtonEvent *event);

void
Mouse_Update(void);
