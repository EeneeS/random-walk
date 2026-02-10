#pragma once

#include <SDL3/SDL.h>

#define MAX_AGENTS 50
#define AGENT_HEIGHT 4
#define AGENT_WIDTH 4
#define SCALE 4

typedef struct {
    void (*quit)(void);
    void (*handle_events)(SDL_Event*);
    void (*update)(void);
    void (*render)(SDL_Renderer*);
} Agent;

typedef struct {
    int dx, dy;
} Direction;

Agent init_agent();

