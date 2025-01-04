#include <game_engine/renderer.h>
#include <game_engine/renderer/vertex_array.h>
#include <game_engine/app.h>

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include <stdlib.h>
#include <stdio.h>

GE_Renderer_t GE_g_renderer = {0};

void GameEngine_RendererResizeCallback(int width, int height) {
    glViewport(0, 0, width, height);
}

void GameEngine_RendererInit() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    GE_g_renderer.context = SDL_GL_CreateContext(GE_g_app.display);
    if(!GE_g_renderer.context) {
        fprintf(stderr, "SDL failed to create OpenGL context!: %s\n", SDL_GetError());
        exit(1);
    }

    if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        fprintf(stderr, "GLAD failed to load OpenGL functions!\n");
        exit(1);
    }

    GE_g_renderer.vsync = true;
    SDL_GL_SetSwapInterval(GE_g_renderer.vsync);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void GameEngine_RendererQuit() {
    SDL_GL_DestroyContext(GE_g_renderer.context);
}

void GameEngine_RendererClear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GameEngine_RendererDraw(const GE_VertexArray_t *vao, const GE_IndexBuffer_t *ibo, const GE_Shader_t *shader) {
    GameEngine_ShaderBind(shader);
    GameEngine_VertexArrayBind(vao);
    GameEngine_IndexBufferBind(ibo);

    glDrawElements(GL_TRIANGLES, ibo->count, GL_UNSIGNED_INT, NULL);
}

void GameEngine_RendererSubmit() {
    SDL_GL_SwapWindow(GE_g_app.display);
}