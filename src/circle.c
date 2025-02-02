#include "../include/circle.h"

static int O_SPEED_X = 1;
static int O_SPEED_Y = 1;

void move_shadow_circle(Circle* circle) {
    circle->x += O_SPEED_X;
    circle->y += O_SPEED_Y;

    if ((circle->x + circle->radius) > WIDTH) {
        circle->x = WIDTH - circle->radius;
        O_SPEED_X = -O_SPEED_X;
    }
    if ((circle->x - circle->radius) < 0) {
        circle->x = circle->radius;
        O_SPEED_X = -O_SPEED_X;
    }
    if ((circle->y + circle->radius) > HEIGHT) {
        circle->y = HEIGHT - circle->radius;
        O_SPEED_Y = -O_SPEED_Y;
    }
    if ((circle->y - circle->radius) < 0) {
        circle->y = circle->radius;
        O_SPEED_Y = -O_SPEED_Y;
    }
}