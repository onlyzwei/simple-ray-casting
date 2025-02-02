#pragma once

#define WIDTH 800
#define HEIGHT 600
// Cores em ARGB (Alpha, Red, Green, Blue)
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_BLACK 0x00000000
#define COLOR_RED   0xFFFF0000
#define RAYS_NUMBER 1080
#define RAY_THICKNESS 3

typedef struct {
    double x, y;
    double radius;
} Circle;

typedef struct {
    double x_start, y_start;
    double angle;
} Ray;