#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>

typedef struct {
    float x, y;
    float dx, dy;
    float height, width;
} Entity;

// ball generator
Entity ball_generator()
{
    Entity ball;
    ball.x = 320;
    ball.y = 240;
    ball.dx = 2.0f;
    ball.dy = 2.0f;
    ball.height = 10.00f;
    ball.width = 10.00f;
    return ball;
}
// renderer
SDL_Renderer *renderer = NULL;

void draw(Entity ball)
{
    SDL_FRect rect = {ball.x, ball.y, ball.width, ball.height};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

int main()
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("Pong", 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS);
    if (window == NULL) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Delay(16);
    SDL_CreateRenderer(window,  &renderer);
    while (true) {
      Entity ball = ball_generator();
    }

    SDL_Quit();
    return 0;
}
