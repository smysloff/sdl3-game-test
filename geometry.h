#pragma once

#include <SDL3/SDL.h>
#include <math.h>

double
GetDegreesFromRadians(double radians);

double
GetRadiansFromDegrees(double degrees);

double
GetAngleBetweenFPoints(SDL_FPoint p1, SDL_FPoint p2);

float
GetDistanceBetweenFPoints(SDL_FPoint p1, SDL_FPoint p2);

SDL_FPoint
GetFPointFromAngle(SDL_FPoint p1, double angle, float distance);
