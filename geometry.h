#pragma once

#include <SDL3/SDL.h>
#include <math.h>

double
getDegreesFromRadians(double radians);

double
getRadiansFromDegrees(double degrees);

double
getAngleBetweenFPoints(SDL_FPoint p1, SDL_FPoint p2);

float
getDistanceBetweenFPoints(SDL_FPoint p1, SDL_FPoint p2);

SDL_FPoint
getFPointFromAngle(SDL_FPoint p1, double angle, float distance);
