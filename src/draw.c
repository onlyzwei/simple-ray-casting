#include "..\include\draw.h"
#include <math.h>

// Função para desenhar um círculo
void FillCircle(SDL_Surface* surface, Circle circle, Uint32 color) {
    double radius_squared = circle.radius * circle.radius; // Calculando o quadrado do raio

    for (double x = circle.x - circle.radius; x <= circle.x; x++) {
        for (double y = circle.y - circle.radius; y <= circle.y; y++) {

            // Se o pixel que está no quadrado faz parte do círculo, então desenha.
            double distance_squared = (x - circle.x) * (x - circle.x) + (y - circle.y) * (y - circle.y); // Calculando a distância ao quadrado
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
    double radius_squared = object.radius * object.radius;

    for (int i = 0; i < RAYS_NUMBER; i++) {
        Ray ray = rays[i];

        // Pré-calcula seno e cosseno para evitar recomputação
        double cos_angle = cos(ray.angle);
        double sin_angle = sin(ray.angle);

        // Define ponto final do raio baseado na tela (ou um limite grande)
        int x1 = (int)(ray.x_start + cos_angle * WIDTH);
        int y1 = (int)(ray.y_start + sin_angle * HEIGHT);

        // Algoritmo de Bresenham para desenhar a linha do raio

        // Pontos iniciais (centro do círculo)
        int x0 = ray.x_start;
        int y0 = ray.y_start;

        // Diferenças entre o ponto final e inicial
        int dx = abs(x1 - x0);
        int dy = abs(y1 - y0);

        // Sentidos de incremento, baseado na direção do raio
        int sx = x0 < x1 ? 1 : -1;
        int sy = y0 < y1 ? 1 : -1;

        int err = dx > dy ? dx : -dy;
        int e2;

        while (x0 >= 0 && x0 < WIDTH && y0 >= 0 && y0 < HEIGHT) {
            // Verifica colisão com o círculo
            if ((x0 - object.x) * (x0 - object.x) + (y0 - object.y) * (y0 - object.y) < radius_squared) {
                break;
            }

            // Desenha o pixel do raio
            SDL_Rect pixel = { x0, y0, RAY_THICKNESS, RAY_THICKNESS };
            SDL_FillRect(surface, &pixel, color);

            // Algoritmo de Bresenham para mover o ponto
            e2 = err;
            if (e2 > -dx) { err -= dy; x0 += sx; }
            if (e2 < dy) { err += dx; y0 += sy; }
        }
    }
}

