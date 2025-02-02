#include "../include/rays.h"
#define _USE_MATH_DEFINES
#include <math.h>

void GenerateRays(Circle circle, Ray rays[RAYS_NUMBER]) {
    for (int i = 0; i < RAYS_NUMBER; i++) {
        double angle = 2 * M_PI * i / RAYS_NUMBER;
        Ray ray = { circle.x, circle.y, angle };
        rays[i] = ray;
    }
}