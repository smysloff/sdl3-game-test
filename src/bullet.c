#include "bullet.h"

Bullet_t bullets[BULLET_COUNT];

SDL_FRect
Bullet_GetRect(Bullet_t *restrict bullet)
{
  return (SDL_FRect) {
    .x = bullet->x, .y = bullet->y,
    .w = bullet->w, .h = bullet->h,
  };
}

void
Bullets_Fire(Character_t *restrict character) // @todo multiple shots at once
{
  for (size_t i = 0; i < BULLET_COUNT; ++i)
  {
    Bullet_t *bullet = bullets + i;
    if (bullet->fired) continue;

    // shoot bullet from the center of character
    // @todo shoot bullet from the gun
    bullet->x = character->x + (character->w - bullet->w) / 2.;
    bullet->y = character->y + (character->h - bullet->h) / 2.;
    bullet->w = BULLET_SIZE;
    bullet->h = BULLET_SIZE;
    bullet->angle = character->angle;
    bullet->speed = BULLET_SPEED;
    bullet->damage = BULLET_DAMAGE;
    bullet->fired = SDL_TRUE;

    break;
  }
}

void
Bullets_Update(float deltatime)
{
  for (size_t i = 0; i < BULLET_COUNT; ++i)
  {
    Bullet_t *bullet = bullets + i;
    if (!bullet->fired) continue;

    SDL_FPoint position = GetFPointFromAngle(
      &(SDL_FPoint){ bullet->x, bullet->y },
      bullet->angle,
      bullet->speed * deltatime
    );

    bullet->x = position.x;
    bullet->y = position.y;

    if (
      bullet->x < 0 || bullet->x > WINDOW_WIDTH ||
      bullet->y < 0 || bullet->y > WINDOW_HEIGHT
    ) {
      bullet->fired = SDL_FALSE;
    }
  }
}

void
Bullets_Render(SDL_Renderer *restrict renderer)
{
  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE);
  for (size_t i = 0; i < BULLET_COUNT; ++i)
  {
    Bullet_t *bullet = bullets + i;
    if (!bullet->fired) continue;
    SDL_FRect rect = Bullet_GetRect(bullet);
    SDL_RenderFillRect(renderer, &rect);
  }
}
