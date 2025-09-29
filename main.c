#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

// ball struct -> pos, velocity, size
typedef struct {
    float x, y;
    float vx, vy;
    int radius;
} Ball;

// draw circle -> using horizontal lines
static void draw_filled_circle(SDL_Renderer *renderer, int cx, int cy, int r) {
    for (int dy = -r; dy <= r; ++dy) {
        int dx = (int)floorf(sqrtf((float)(r * r - dy * dy)));
        SDL_RenderLine(renderer, (float)(cx - dx), (float)(cy + dy),
                                     (float)(cx + dx), (float)(cy + dy));
    }
}

int main(int argc, char *argv[]) {
    (void)argc; (void)argv;

    // init SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }

    const int WIN_W = 800;
    const int WIN_H = 600;

    // window + renderer
    SDL_Window *win = SDL_CreateWindow("SDL3 Ball Bounce", WIN_W, WIN_H, 0);
    if (!win) {
        fprintf(stderr, "SDL_CreateWindow error: %s\n", SDL_GetError());
        SDL_Quit();
        return 2;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(win, NULL);
    if (!renderer) {
        fprintf(stderr, "SDL_CreateRenderer error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 3;
    }

    // setup ball
    Ball ball = {
        .x = WIN_W * 0.25f,
        .y = WIN_H * 0.25f,
        .vx = 240.0f,
        .vy = 160.0f,
        .radius = 20
    };

    Uint64 last_ticks = SDL_GetTicks();
    bool running = true;
    SDL_Event event;

    // main loop
    while (running) {
        // input
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
            if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_ESCAPE) running = false;
            }
        }

        // time step
        Uint64 now = SDL_GetTicks();
        float dt = (now - last_ticks) / 1000.0f;
        if (dt > 0.05f) dt = 0.05f;
        last_ticks = now;

        // move ball
        ball.x += ball.vx * dt;
        ball.y += ball.vy * dt;

        // bounce walls
        if (ball.x - ball.radius <= 0) {
            ball.x = ball.radius;
            ball.vx = -ball.vx;
        } else if (ball.x + ball.radius >= WIN_W) {
            ball.x = WIN_W - ball.radius;
            ball.vx = -ball.vx;
        }
        if (ball.y - ball.radius <= 0) {
            ball.y = ball.radius;
            ball.vy = -ball.vy;
        } else if (ball.y + ball.radius >= WIN_H) {
            ball.y = WIN_H - ball.radius;
            ball.vy = -ball.vy;
        }

        // draw
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        SDL_FRect border = { 2.0f, 2.0f, (float)(WIN_W - 4), (float)(WIN_H - 4) };
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderRect(renderer, &border);

        SDL_SetRenderDrawColor(renderer, 220, 80, 80, 255);
        draw_filled_circle(renderer, (int)roundf(ball.x), (int)roundf(ball.y), ball.radius);

        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }

    // cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}