#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600
// Cores em ARGB (Alpha, Red, Green, Blue)
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_BLACK 0x00000000
#define COLOR_RED   0xFFFF0000
#define RAYS_NUMBER 360
#define RAY_THICKNESS 5

int O_SPEED_X = 1;
int O_SPEED_Y = 1;

typedef struct {
    double x, y;
    double radius;
} Circle;

typedef struct {
    double x_start, y_start;
    double angle;
} Ray;

// Função para desenhar um círculo
void FillCircle(SDL_Surface* surface, Circle circle, Uint32 color) {
    double radius_squared = pow(circle.radius, 2);

    for (double x = circle.x - circle.radius; x <= circle.x; x++) {
        for (double y = circle.y - circle.radius; y <= circle.y; y++) {

            // Se o pixel que está no quadrado faz parte do círculo, então desenha.
            double distance_squared = pow(x - circle.x, 2) + pow(y - circle.y, 2);
            if (distance_squared < radius_squared) {
                SDL_Rect pixel = (SDL_Rect){ x, y, 1, 1 };

                // Espelhamento no eixo X (horizontal)
                SDL_Rect pixel_mirrored_x = (SDL_Rect){ 2 * circle.x - x, y, 1, 1 };

                // Espelhamento no eixo Y (vertical)
                SDL_Rect pixel_mirrored_y = (SDL_Rect){ x, 2 * circle.y - y, 1, 1 };

                // Espelhamento nos dois eixos (XY)
                SDL_Rect pixel_mirrored_xy = (SDL_Rect){ 2 * circle.x - x, 2 * circle.y - y, 1, 1 };

                SDL_FillRect(surface, &pixel, color);
                SDL_FillRect(surface, &pixel_mirrored_x, color);
                SDL_FillRect(surface, &pixel_mirrored_y, color);
                SDL_FillRect(surface, &pixel_mirrored_xy, color);
            }
        }
    }
}

void FillRays(SDL_Surface* surface, Ray rays[RAYS_NUMBER], Circle object, Uint32 color) {

    double radius_squared = pow(object.radius, 2);

    for (int i = 0; i < RAYS_NUMBER; i++) {
        Ray ray = rays[i];

        int end_of_screen = 0;
        int object_hit = 0;

        int step = 1;
        double x_draw = ray.x_start;
        double y_draw = ray.y_start;

        while (end_of_screen == 0 && object_hit == 0) {
            // Calcula a posição do pixel
            x_draw += step * cos(ray.angle);
            y_draw += step * sin(ray.angle);

            // Verifica se o pixel está dentro da tela
            if (x_draw < 0 || x_draw >= WIDTH || y_draw < 0 || y_draw >= HEIGHT) {
                end_of_screen = 1;
                continue;
            }

            // Verifica se o pixel está colidindo com o círculo
            double distance_squared = pow(x_draw - object.x, 2) + pow(y_draw - object.y, 2);
            if (distance_squared < radius_squared) {
                object_hit = 1;
                continue;
            }

            // Desenha o pixel
            SDL_Rect ray_pixel = (SDL_Rect){ x_draw, y_draw, RAY_THICKNESS, RAY_THICKNESS };
            SDL_FillRect(surface, &ray_pixel, color);
        }
    }
}

void GenerateRays(Circle circle, Ray rays[RAYS_NUMBER]) {
    for (int i = 0; i < RAYS_NUMBER; i++) {
        // Distribuir cada raio uniformemente ao redor do círculo, em radianos. 
        double angle = 2 * M_PI * i / RAYS_NUMBER;

        Ray ray = { circle.x, circle.y, angle };
        rays[i] = ray;
    }
}

// Função para mover o círculo sombra
void move_shadow_circle(Circle* circle) {
    circle->x += O_SPEED_X;
    circle->y += O_SPEED_Y;
    // Se colide com a parede direita
    if ((circle->x + circle->radius) > WIDTH) {
        // conserta o circulo 
        circle->x = WIDTH - circle->radius;
        O_SPEED_X = -O_SPEED_X;
    }
    // Se colide com a parede esquerda
    if ((circle->x - circle->radius) < 0) {
        // conserta o circulo 
        circle->x = circle->radius;
        O_SPEED_X = -O_SPEED_X;
    }
    // Se colide com a parede de baixo
    if ((circle->y + circle->radius) > HEIGHT) {
        // conserta o circulo 
        circle->y = HEIGHT - circle->radius;
        O_SPEED_Y = -O_SPEED_Y;
    }
    // Se colide com a parede de cima
    if ((circle->y - circle->radius) < 0) {
        // conserta o circulo 
        circle->y = circle->radius;
        O_SPEED_Y = -O_SPEED_Y;
    }
}

int SDL_main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erro ao inicializar SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

    SDL_Surface* surface = SDL_GetWindowSurface(window);

    // Define o círculo
    Circle circle = { WIDTH / 2, HEIGHT / 2, 50 };
    Circle shadow_circle = { 650, 300, 75 };

    // Define os raios
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

        // Limpa a tela a cada frame
        SDL_FillRect(surface, NULL, COLOR_BLACK);

        // Gera os raios
        GenerateRays(circle, rays);

        // Desenha os raios
        FillRays(surface, rays, shadow_circle, COLOR_RED);

        // Desenha o círculo
        FillCircle(surface, circle, COLOR_WHITE);
        FillCircle(surface, shadow_circle, COLOR_WHITE);

        // 
        move_shadow_circle(&shadow_circle);

        // Atualiza a tela
        SDL_UpdateWindowSurface(window);
        SDL_Delay(10);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}