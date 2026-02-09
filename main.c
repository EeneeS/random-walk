#include <SDL3/SDL.h>
#include <SDL3/SDL_stdinc.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 900
#define HEIGHT 600
#define SPEED 10

typedef struct {
    int dx, dy;
} Direction;

typedef struct {
    int x, y;
    Uint8 r, g, b; // Individual color components
} Agent;

Direction get_rand_direction() {
    int dir = rand() % 4;
    switch (dir) {
        case 0: return (Direction){0, 1};
        case 1: return (Direction){0, -1};
        case 2: return (Direction){-1, 0};
        case 3: return (Direction){1, 0};
    }
    fprintf(stderr, "Impossible random value %d encountered\n", dir);
    exit(-1);
}

void create_agents(Agent *pagents, int num_agents) {
    for (int i = 0; i < num_agents; i++) {
        pagents[i] = (Agent){
            WIDTH / 2, 
            HEIGHT / 2, 
            (Uint8)(50 + (i * 110) % 206), 
            (Uint8)(50 + (i * 160) % 206), 
            (Uint8)(50 + (i * 210) % 206)
        };
    }
}

void move_agent(SDL_Renderer *prenderer, Agent *pagent) {
    SDL_SetRenderDrawColor(prenderer, pagent->r, pagent->g, pagent->b, 255);
    Direction direction = get_rand_direction();
    for (int i = 0; i < SPEED; i++) {
        pagent->x += direction.dx;
        pagent->y += direction.dy;
        SDL_FRect rect = (SDL_FRect){(float)pagent->x, (float)pagent->y, 2, 2};
        SDL_RenderFillRect(prenderer, &rect);
    }
}

int main(int argc, const char *argv[]) {
    int num_agents;
    if (argc == 1) {
        num_agents = 5;
    } else if (argc == 2) {
        num_agents = atoi(argv[1]);
    } else {
        printf("Usage: %s <num-of-agents>\n", argv[0]);
        return -1;
    }

    srand(time(NULL));

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *pwindow = SDL_CreateWindow("Random Walk", WIDTH, HEIGHT, 0);
    SDL_Renderer *prenderer = SDL_CreateRenderer(pwindow, NULL);
    SDL_Texture *pcanvas = SDL_CreateTexture(prenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);
    
    SDL_SetRenderTarget(prenderer, pcanvas);
    SDL_SetRenderDrawColor(prenderer, 0, 0, 0, 255);
    SDL_RenderClear(prenderer);

    Agent *pagents = calloc(num_agents, sizeof(Agent));
    create_agents(pagents, num_agents);

    int app_running = 1;
    while (app_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                app_running = 0;
            }
        }

        SDL_SetRenderTarget(prenderer, pcanvas);
        SDL_SetRenderDrawColor(prenderer, 255, 255, 255, 255);

        for (int i = 0; i < num_agents; i++) {
            move_agent(prenderer, &pagents[i]);
        }

        SDL_SetRenderTarget(prenderer, NULL);
        SDL_RenderTexture(prenderer, pcanvas, NULL, NULL);
        SDL_RenderPresent(prenderer);

        SDL_Delay(33);
    }

    SDL_DestroyTexture(pcanvas);
    SDL_DestroyRenderer(prenderer);
    SDL_DestroyWindow(pwindow);
    SDL_Quit();
    return 0;
}
