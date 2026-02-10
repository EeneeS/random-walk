#include <SDL3/SDL.h>
#include <stdlib.h>
#include "main.h"
#include "agent.h"

Direction get_random_direction() {
    int dir = rand() % 4;
    switch(dir) {
        case 0: return (Direction) {1, 0};
        case 1: return (Direction) {-1, 0};
        case 2: return (Direction) {0, -1};
        case 3: return (Direction) {0, 1};
    }
    return (Direction) {0, 0};
}

SDL_Color get_random_color() {
    return (SDL_Color){
        50 + rand() % 206,
        50 + rand() % 206,
        50 + rand() % 206,
        255
    };
}

static void quit(AgentState *state) {
    free(state);
}

static void handle_events(SDL_Event *event, AgentState *state) {
}

static void update(AgentState *state) {
    if (state->steps_remaining <= 0) {
        Direction new_direction;
        do {
            new_direction = get_random_direction();
        } while (new_direction.dx == -state->current_direction.dx && 
                 new_direction.dy == -state->current_direction.dy);
        
        state->current_direction = new_direction;
        state->steps_remaining = 3;
    }
    
    state->rect.x += state->current_direction.dx * 3;
    state->rect.y += state->current_direction.dy * 3;
    state->steps_remaining--;
}

static void render(SDL_Renderer *prenderer, AgentState *state) {
    SDL_SetRenderDrawColor(prenderer, state->color.r, state->color.g, state->color.b, 255); 
    SDL_RenderFillRect(prenderer, &state->rect);
}

Agent init_agent() {
    AgentState *state = malloc(sizeof(AgentState));
    *state = (AgentState){
        .rect = {WIDTH/2, HEIGTH/2, AGENT_WIDTH, AGENT_HEIGHT},
        .current_direction = {1, 0},
        .steps_remaining = 0,
        .color = get_random_color()
    };
    
    Agent agent = (Agent) {
        .quit = quit,
        .handle_events = handle_events,
        .update = update,
        .render = render,
        .state = state
    };
    return agent;
}
