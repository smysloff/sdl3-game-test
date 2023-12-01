#include "character.h"

Character_t player = {
  .x = PLAYER_X,    .y = PLAYER_Y,    // position
  .w = PLAYER_SIZE, .h = PLAYER_SIZE, // size
  .health = PLAYER_HEALTH,
  .atackStatus = ATACK_STATUS_IDLE,
};

SDL_FRect
Character_GetRect(Character_t *restrict character)
{
  return (SDL_FRect) {
    .x = character->x, .y = character->y,
    .w = character->w, .h = character->h,
  };
}
