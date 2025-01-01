#pragma once
#include <game_engine/renderer/index_buffer.h>
#include <game_engine/renderer/vertex_buffer.h>
#include <game_engine/renderer/vertex_array.h>
#include <game_engine/renderer/buffer_layout.h>
#include <game_engine/renderer/shader.h>

#include <stdbool.h>

typedef struct {
    void *context;
    bool vsync;
} GE_Renderer_t;
extern GE_Renderer_t GE_g_renderer;

void GameEngine_RendererResizeCallback(int width, int height);

void GameEngine_RendererInit();
void GameEngine_RendererQuit();

void GameEngine_RendererDraw(const GE_VertexArray_t *vao, const GE_IndexBuffer_t *ibo, const GE_Shader_t *shader);