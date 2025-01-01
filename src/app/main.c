#include <game_engine/app.h>
#include <game_engine/renderer.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

// For testing
#include <SDL3/SDL.h>
#include <glad/glad.h>

float vertices[] = {
    -0.5f, -0.5f,
     0.5f, -0.5f,
     0.5f,  0.5f,
    -0.5f,  0.5f
};

unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
};

GE_VertexArray_t vao;
GE_VertexBuffer_t vbo;
GE_IndexBuffer_t ibo;
GE_BufferLayout_t layout;
GE_Shader_t shader;

void mainloop() {
    GameEngine_AppProcess();

// Testing
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GameEngine_RendererDraw(&vao, &ibo, &shader);

    SDL_GL_SwapWindow(GE_g_app.display);
}

int main() {
    GameEngine_AppInit();
    GameEngine_RendererInit();

    vao = GameEngine_VertexArrayCreate();
    GameEngine_VertexArrayBind(&vao);

    vbo = GameEngine_VertexBufferCreate(vertices, sizeof(vertices));
    GameEngine_BufferLayoutAddAttribute(&layout, GL_FLOAT, 2, GL_FALSE);
    GameEngine_BufferLayoutUse(&layout);

    ibo = GameEngine_IndexBufferCreate(indices, 6);
    GameEngine_ShaderInit(&shader, "data/shaders/engine/basic.vert", "data/shaders/engine/basic.frag");

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainloop, 60, 1);
#else
    while(*GameEngine_AppIsRunning()) {
        mainloop();
    }
#endif

    GameEngine_VertexArrayDestroy(&vao);
    GameEngine_ShaderDestroy(&shader);
    GameEngine_BufferLayoutDestroy(&layout);
    GameEngine_IndexBufferDestroy(&ibo);
    GameEngine_VertexBufferDestroy(&vbo);
    GameEngine_RendererQuit();
    GameEngine_AppQuit();
    return 0;
}