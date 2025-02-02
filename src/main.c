#include <SDL2/SDL.h>
#include <stdio.h>
#include "../include/types.h"
#include "../include/draw.h"
#include "../include/rays.h"
#include "../include/circle.h"

int SDL_main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erro ao inicializar SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Surface* surface = SDL_GetWindowSurface(window);

    Circle circle = { WIDTH / 2, HEIGHT / 2, 50 };
    Circle shadow_circle = { 650, 300, 75 };
    Ray rays[RAYS_NUMBER];

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if (event.type == SDL_MOUSEMOTION && event.motion.state != 0) {
                circle.x = event.motion.x;
                circle.y = event.motion.y;
            }
        }

        SDL_FillRect(surface, NULL, COLOR_BLACK);
        GenerateRays(circle, rays);
        FillRays(surface, rays, shadow_circle, COLOR_RED);
        FillCircle(surface, circle, COLOR_WHITE);
        FillCircle(surface, shadow_circle, COLOR_WHITE);
        move_shadow_circle(&shadow_circle);

        SDL_UpdateWindowSurface(window);
        SDL_Delay(10);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}