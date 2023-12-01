#include "mouse.h"

Mouse_t mouse;

void
Mouse_ButtonDown_Handler(SDL_MouseButtonEvent *event)
{
  switch (event->button)
  {
    case SDL_BUTTON_LEFT:   mouse.left   = SDL_TRUE; break;
    case SDL_BUTTON_MIDDLE: mouse.middle = SDL_TRUE; break;
    case SDL_BUTTON_RIGHT:  mouse.right  = SDL_TRUE; break;
    case SDL_BUTTON_X1:     mouse.x1     = SDL_TRUE; break;
    case SDL_BUTTON_X2:     mouse.x2     = SDL_TRUE; break;
    default: break;
  }
}

void
Mouse_ButtonUp_Handler(SDL_MouseButtonEvent *event)
{
  switch (event->button)
  {
    case SDL_BUTTON_LEFT:   mouse.left   = SDL_FALSE; break;
    case SDL_BUTTON_MIDDLE: mouse.middle = SDL_FALSE; break;
    case SDL_BUTTON_RIGHT:  mouse.right  = SDL_FALSE; break;
    case SDL_BUTTON_X1:     mouse.x1     = SDL_FALSE; break;
    case SDL_BUTTON_X2:     mouse.x2     = SDL_FALSE; break;
    default: break;
  }
}

void
Mouse_Update(void)
{
  if (SDL_GetMouseFocus())
    SDL_GetMouseState(&mouse.x, &mouse.y);
}
