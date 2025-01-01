#include <game_engine/app.h>
GE_App_t GE_g_app = {0};

#include <SDL3/SDL.h>

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int monitor_width, monitor_height;
    int window_width, window_height;
    bool fullscreen;
} AppState_t;
AppState_t app_state = {0};

const bool *GameEngine_AppIsRunning() {
    return &GE_g_app.running;
}

const bool *GameEngine_AppToggleFullscreen() {
    app_state.fullscreen = !app_state.fullscreen;
    SDL_SetWindowFullscreen(GE_g_app.display, (app_state.fullscreen ? SDL_WINDOW_FULLSCREEN : 0));
    return &app_state.fullscreen;
}

void GameEngine_AppInit() {
    if(!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL failed to initialize!: %s\n", SDL_GetError());
        exit(1);
    }

    {
        const SDL_DisplayMode *mode = SDL_GetCurrentDisplayMode(SDL_GetPrimaryDisplay());
        app_state.monitor_width = mode->w;
        app_state.monitor_height = mode->h;
        app_state.window_width = mode->w/2;
        app_state.window_height = mode->h/2;
    }

    GE_g_app.display = SDL_CreateWindow(NULL, app_state.monitor_width/2, app_state.window_height, SDL_WINDOW_OPENGL);
    if(!GE_g_app.display) {
        fprintf(stderr, "SDL failed to create window!: %s\n", SDL_GetError());
        exit(1);
    }

    app_state.fullscreen = false;
    GE_g_app.running = true;
}

void GameEngine_AppQuit() {
    SDL_DestroyWindow(GE_g_app.display);
    SDL_Quit();
}

void GameEngine_AppProcess() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_EVENT_QUIT: {
                GE_g_app.running = false;
            } break;
            case SDL_EVENT_KEY_DOWN: {
                if (event.key.scancode == SDL_SCANCODE_F11) {
                    GameEngine_AppToggleFullscreen();
                }
            }
            case SDL_EVENT_WINDOW_RESIZED: {
                SDL_GetWindowSize(GE_g_app.display, &app_state.window_width, &app_state.window_height);
                GameEngine_RendererResizeCallback(app_state.window_width, app_state.window_height);
            }
        }
    }
}