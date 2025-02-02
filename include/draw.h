#pragma once
#include <SDL2/SDL.h>
#include "types.h"

void FillCircle(SDL_Surface* surface, Circle circle, Uint32 color);
void DrawLineBresenham(SDL_Surface* surface, int x0, int y0, int x1, int y1, Uint32 color, Circle object);
void FillRays(SDL_Surface* surface, Ray rays[RAYS_NUMBER], Circle object, Uint32 color);
