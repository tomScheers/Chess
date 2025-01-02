#pragma once

#include <stdbool.h>

typedef struct {
    void *display;
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