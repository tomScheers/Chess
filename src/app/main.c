#include <game_engine/app.h>
#include <game_engine/renderer.h>
#include <game_engine/renderer/index_buffer.h>
#include <game_engine/renderer/vertex_buffer.h>
#include <game_engine/renderer/buffer_layout.h>
#include <game_engine/renderer/shader.h>
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

unsigned int vao;
GE_VertexBuffer_t vbo;
GE_IndexBuffer_t ibo;
GE_BufferLayout_t layout;
GE_Shader_t shader;

void mainloop() {
    GameEngine_AppProcess();

// Testing
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GameEngine_ShaderUse(&shader);

    glBindVertexArray(vao);

    GameEngine_VertexBufferBind(&vbo);
    GameEngine_IndexBufferBind(&ibo);

    glDrawElements(GL_TRIANGLES, ibo.count, GL_UNSIGNED_INT, NULL);

    SDL_GL_SwapWindow(GE_g_app.display);
}

int main() {
    GameEngine_AppInit();
    GameEngine_RendererInit();

// Testing
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    vbo = GameEngine_VertexBufferCreate(vertices, 4 * 2 * sizeof(float));
    GameEngine_BufferLayoutAddAttribute(&layout, GL_FLOAT, 2, GL_FALSE);
    GameEngine_BufferLayoutUse(&layout);

    ibo = GameEngine_IndexBufferCreate(indices, 6);
    GameEngine_ShaderInit(&shader, "data/basic.vert", "data/basic.frag");


#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainloop, 60, 1);
#else
    while(*GameEngine_AppIsRunning()) {
        mainloop();
    }
#endif

    GameEngine_ShaderDestroy(&shader);
    GameEngine_BufferLayoutDestroy(&layout);
    GameEngine_IndexBufferDestroy(&ibo);
    GameEngine_VertexBufferDestroy(&vbo);
    GameEngine_RendererQuit();
    GameEngine_AppQuit();
    return 0;
}