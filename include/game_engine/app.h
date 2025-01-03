#pragma once

#include <stdbool.h>

typedef struct {
    void *display;
    int display_width, display_height;
    bool running;
} GE_App_t;
extern GE_App_t GE_g_app;

typedef struct {
    int mouse_x, mouse_y;
    bool keys[256], mouse_buttons[5];
} GE_InputState_t;
extern GE_InputState_t GE_g_input_state;

extern void GameEngine_RendererResizeCallback(int width, int height);

const bool *GameEngine_AppIsRunning();
const bool *GameEngine_AppToggleFullscreen();

void GameEngine_AppInit();
void GameEngine_AppQuit();
void GameEngine_AppProcess();

typedef struct {
    void (*init)(void), (*shutdown)(void), (*update)(double dt), (*renderpass)();
} GE_ProjectCallbacks_t;

// Defined in project
GE_ProjectCallbacks_t Game_Entry();