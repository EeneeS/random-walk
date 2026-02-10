#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_pixels.h>

#define MAX_AGENTS 10
#define AGENT_HEIGHT 4
#define AGENT_WIDTH 4
#define SCALE 4

typedef struct {
    int dx, dy;
} Direction;

typedef struct {
    SDL_FRect rect;
    Direction current_direction;
    int steps_remaining;
    SDL_Color color;
} AgentState;

typedef struct {
    void (*quit)(AgentState*);
    void (*handle_events)(SDL_Event*, AgentState*);
    void (*update)(AgentState*);
    void (*render)(SDL_Renderer*, AgentState*);
    AgentState *state;
} Agent;


Agent init_agent();

