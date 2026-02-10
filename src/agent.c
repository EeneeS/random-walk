#include <SDL3/SDL.h>
#include <stdlib.h>

#include "main.h"
#include "agent.h"

SDL_FRect rect = {WIDTH/2, HEIGTH/2, AGENT_WIDTH, AGENT_HEIGHT};

Direction get_random_direction() {
    int dir = rand() % 4;
    switch(dir) {
        case 0: // RIGHT
            return (Direction) {1, 0};
            break;
        case 1: // LEFT
            return (Direction) {-1, 0};
            break;
        case 2: // UP
            return (Direction) {0, 1};
            break;
        case 3: // DOWN
            return (Direction) {0, -1};
            break;
    }
    return (Direction) {0, 0};
}

static void quit() {
}

static void hande_events(SDL_Event *event) {
}

static void update() {
    Direction direction = get_random_direction();
    for (int i = 0; i < SCALE; i++) {
        rect.x += direction.dx;
        rect.y += direction.dy;
    }
}

static void render(SDL_Renderer *prenderer) {
    SDL_SetRenderDrawColor(prenderer, 255, 255, 255, 255); 
    SDL_RenderFillRect(prenderer, &rect);
}

Agent init_agent() {
    Agent agent = (Agent) {
        .quit = quit,
        .handle_events = hande_events,
        .update = update,
        .render = render
    };
    return agent;
}
