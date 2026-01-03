#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>

// macros
#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 720

// entity

typedef struct {
    float x, y;
    float dx, dy;
    float height, width;
} Entity;

// paddle type
typedef enum {
    PADDLE_LEFT,
    PADDLE_RIGHT
} PaddleSide;

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

void ball_update( Entity *ball ,bool left_paddle, bool right_paddle);
void keyboard_input (Entity *paddle1 , Entity *paddle2);
bool check_collision(Entity *ball, Entity *paddle);

// renderer
SDL_Renderer* renderer = NULL;

//ball
void draw(const Entity ball, const Entity paddle1, const Entity paddle2)
{
    SDL_FRect rect1 = {ball.x, ball.y, ball.width, ball.height};
    SDL_FRect rect2 = {paddle1.x, paddle1.y, paddle1.width, paddle1.height};
    SDL_FRect rect3 = {paddle2.x, paddle2.y, paddle2.width, paddle2.height};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect1);
    SDL_RenderFillRect(renderer, &rect2);
    SDL_RenderFillRect(renderer, &rect3);
}

//paddle
Entity paddle_generator(PaddleSide const side)
{
    Entity paddle;
    paddle.x = 10.00;
    paddle.y = WINDOW_HEIGHT/2;
    paddle.dx = 0.0f;
    paddle.dy = 4.0f;
    paddle.height = 45.00f;
    paddle.width = 8.00f;

    if (side == PADDLE_RIGHT)
    {
        paddle.x = WINDOW_WIDTH - paddle.width;
    }
    return paddle;
}

// main function

int main()
{

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("Pong Game", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS);
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
    Entity paddle1 = paddle_generator(PADDLE_LEFT);
    Entity paddle2 = paddle_generator(PADDLE_RIGHT);
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
        draw(ball,paddle1, paddle2);
        ball_update(&ball, check_collision(&ball, &paddle1), check_collision(&ball, &paddle2));
        keyboard_input(&paddle1, &paddle2);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);

    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

// ball update

void ball_update( Entity *ball ,bool left_paddle, bool right_paddle)
{
    ball->x += ball->dx;
    ball->y += ball->dy;
    if (ball->x < 0 && ball->dx < 0) {
        ball->dx = -ball->dx;
    }
    if (ball->x > WINDOW_WIDTH - ball->width && ball->dx > 0) {
        ball->dx = -ball->dx;
    }
    if (ball->y < 0 && ball->dy < 0) {
        ball->dy = -ball->dy;
    }
    if (ball->y > WINDOW_HEIGHT - ball->height && ball->dy > 0) {
        ball->dy = -ball->dy;
    }
}

//keyboard input
void keyboard_input (Entity *paddle1 , Entity *paddle2)
    {
    const bool* state = SDL_GetKeyboardState(NULL);
        // W pressed or not
     if (state[SDL_SCANCODE_W] && paddle1->y > 0)
     {
         paddle1->y -= paddle1->dy;
     }
        // S pressed or not
        if (state[SDL_SCANCODE_S] && paddle1->y < WINDOW_HEIGHT - paddle1->height)
        {
            paddle1->y += paddle1->dy;
        }
         // up arrow pressed or not
     if (state[SDL_SCANCODE_UP] && paddle2->y > 0)
     {
         paddle2->y -= paddle2->dy;
     }
        // down arrow pressed or not
        if (state[SDL_SCANCODE_DOWN] && paddle2->y < WINDOW_HEIGHT - paddle2->height)
        {
            paddle2->y += paddle2->dy;
        }
    };

bool check_collision(Entity *ball, Entity *paddle)
{
    if (ball->x < paddle->x + paddle->width &&
        ball->x + ball->width > paddle->x &&
        ball->y < paddle->y + paddle->height &&
        ball->y + ball->height > paddle->y)
    {
        ball->dx = -ball->dx;
        return true;
    }else {
        return false;
    }
};