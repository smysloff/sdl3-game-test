#pragma once

#include <SDL3/SDL.h>
#include "config.h"

typedef enum AtackStatus_e
{
  ATACK_STATUS_IDLE,
  ATACK_STATUS_SHOT,
  ATACK_STATUS_WAIT,
} AtackStatus_t;

typedef struct Character_s
{
  float x, y;
  float w, h;
  double angle;
  int health;
  float speed;
  AtackStatus_t atackStatus;
} Character_t;

SDL_FRect*
Character_GetRect(Character_t *character);
