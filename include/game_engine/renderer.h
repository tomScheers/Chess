#pragma once

#include <stdbool.h>

typedef struct {
    void *context;
    bool vsync;
} GE_Renderer_t;
extern GE_Renderer_t GE_g_renderer;

void GameEngine_RendererResizeCallback(int width, int height);

void GameEngine_RendererInit();
void GameEngine_RendererQuit();