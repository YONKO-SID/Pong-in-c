#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>

// macros
#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 640

// entity

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
    ball.height = 8.00f;
    ball.width = 8.00f;
    return ball;
}

void ball_update( Entity *ball);
void keyboard_input (Entity *paddle);

// renderer
SDL_Renderer* renderer = NULL;

//ball
void draw(const Entity ball, const Entity paddle)
{
    SDL_FRect rect1 = {ball.x, ball.y, ball.width, ball.height};
    SDL_FRect rect2 = {paddle.x, paddle.y, paddle.width, paddle.height};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect1);
    SDL_RenderFillRect(renderer, &rect2);
}

//paddle
Entity paddle_generator()
{
    Entity paddle;
    paddle.x = 320;
    paddle.y = 240;
    paddle.dx = 0.0f;
    paddle.dy = 0.0f;
    paddle.height = 29.00f;
    paddle.width = 8.00f;
    return paddle;
}

// main function

int main()
{

    if (!SDL_Init(SDL_INIT_VIDEO) != false) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("Pong Game", WINDOW_HEIGHT, WINDOW_WIDTH, SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS);
    if (window == NULL) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    bool running = true;
    SDL_Delay(16);
    renderer = SDL_CreateRenderer(window,  NULL);
    if (renderer == NULL) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    Entity ball = ball_generator();
    Entity paddle = paddle_generator();
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                SDL_RenderClear(renderer);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                running = false;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw(ball,paddle);
        ball_update(&ball);
        keyboard_input(&paddle);


        SDL_RenderPresent(renderer);
        SDL_Delay(16);

    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

// ball update

void ball_update( Entity *ball)
{
    ball->x += ball->dx;
    ball->y += ball->dy;
    if (ball->x < 0) {
        ball->dx = -ball->dx;
    }
    if (ball->x > WINDOW_WIDTH - ball->width) {
        ball->dx = -ball->dx;
    }
    if (ball->y < 0) {
        ball->dy = -ball->dy;
    }
    if (ball->y > WINDOW_HEIGHT - ball->height) {
        ball->dy = -ball->dy;
    }
}

//keyboard input
void keyboard_input (Entity *paddle)
{
    const bool* state = SDL_GetKeyboardState(NULL);
    {
        // W pressed or not
     if (state[SDL_SCANCODE_W])
     {
         paddle->y -= paddle->dy;
     }
        // S pressed or not
        if (state[SDL_SCANCODE_S])
        {
            paddle->y += paddle->dy;
        }
    };
}