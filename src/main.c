#define SDL_MAIN_USE_CALLBACKS

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_timer.h>
#include <stdlib.h>
#include <time.h>

#include "main.h"
#include "agent.h"

SDL_Window *pwindow;
SDL_Renderer *prenderer;
SDL_Texture *ptexture;

Agent agents[MAX_AGENTS];
int agent_count = 0;

void handle_event_agents(SDL_Event *event) {
    for (int i = 0; i < agent_count; i++) {
        agents[i].handle_events(event, agents[i].state);
    }
}

void render_agents() {
    for (int i = 0; i < agent_count; i++) {
        agents[i].render(prenderer, agents[i].state);
    }
}

void update_agents() {
    for (int i = 0; i < agent_count; i++) {
        agents[i].update(agents[i].state);
    }
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    srand(time(NULL));

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Error initializing SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    pwindow = SDL_CreateWindow("Random walk", WIDTH, HEIGTH, 0);
    if (!pwindow) {
        SDL_Log("Error initializing window: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    prenderer = SDL_CreateRenderer(pwindow, 0);
    if (!prenderer) {
        SDL_Log("Error initializing renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    ptexture = SDL_CreateTexture(prenderer,SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGTH);
    if (!ptexture) {
        SDL_Log("Error initializing texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderTarget(prenderer, ptexture);
    SDL_SetRenderDrawColor(prenderer, 45, 45, 48, 255);
    SDL_RenderClear(prenderer);
    SDL_SetRenderTarget(prenderer, 0);

    for (int i = 0; i < MAX_AGENTS; i++) {
        agents[i] = init_agent();
    }
    agent_count = MAX_AGENTS; 

    return SDL_APP_CONTINUE;
}

void update() {
    update_agents();
}

void render() {
    SDL_SetRenderTarget(prenderer, ptexture);
    render_agents();
    SDL_SetRenderTarget(prenderer, NULL);

    SDL_RenderTexture(prenderer, ptexture, 0, 0);
    SDL_RenderPresent(prenderer);
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    update();
    render();
    SDL_Delay(16);
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    handle_event_agents(event);
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    SDL_DestroyRenderer(prenderer);
    SDL_DestroyWindow(pwindow);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
}
