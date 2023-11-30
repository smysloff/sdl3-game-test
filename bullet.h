#pragma once

#include <SDL3/SDL.h>
#include "config.h"
#include "geometry.h"
#include "character.h"


typedef struct Bullet_s
{
  float    x, y;
  float    w, h;
  double   angle;
  float    speed;
  int      damage;
  SDL_bool fired;
} Bullet_t;

void
Bullets_Fire(Character_t *character);

void
Bullets_Update(float deltatime);

void
Bullets_Render(SDL_Renderer *renderer);
