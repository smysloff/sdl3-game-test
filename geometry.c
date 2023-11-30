#include "geometry.h"

double
getDegreesFromRadians(double radians)
{
  return radians * (180 / M_PI);
}

double
getRadiansFromDegrees(double degrees)
{
  return degrees * (M_PI / 180);
}

double
getAngleBetweenFPoints(SDL_FPoint p1, SDL_FPoint p2)
{
  return atan2(p2.y - p1.y, p2.x - p1.x);
}

float
getDistanceBetweenFPoints(SDL_FPoint p1, SDL_FPoint p2)
{
  float dx = p2.x - p1.x;
  float dy = p2.y - p1.y;
  return sqrt(dx * dx + dy * dy);
}

SDL_FPoint
getFPointFromAngle(SDL_FPoint point, double angle, float distance)
{
  return (SDL_FPoint) {
    .x = point.x + distance * cos(angle),
    .y = point.y + distance * sin(angle)
  };
}
