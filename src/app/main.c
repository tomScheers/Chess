#include <game_engine/app.h>
#include <game_engine/renderer.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

// #include <cglm/cglm.h>

// For testing
#include <SDL3/SDL.h>
#include <glad/glad.h>

float vertices[] = {
    -0.5f, -0.5f, 0.0f, 0.0f,
     0.5f, -0.5f, 1.0f, 0.0f,
     0.5f,  0.5f, 1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f, 1.0f
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
GE_Texture_t texture;

void mainloop() {
    GameEngine_AppProcess();

    GameEngine_RendererClear();
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
    GameEngine_BufferLayoutAddAttribute(&layout, GL_FLOAT, 2, GL_FALSE);
    GameEngine_BufferLayoutUse(&layout);

    ibo = GameEngine_IndexBufferCreate(indices, 6);

    texture = GameEngine_TextureCreate("data/image/test.png");
    GameEngine_TextureBind(&texture, 0);

    // GameEngine_ShaderInit(&shader, "data/shaders/engine/basic.vert", "data/shaders/engine/basic.frag");
    GameEngine_ShaderInit(&shader, "data/shaders/engine/textured.vert", "data/shaders/engine/textured.frag");
    GameEngine_ShaderSetUniformInt(&shader, "u_texture", 0);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainloop, 60, 1);
#else
    while(*GameEngine_AppIsRunning()) {
        mainloop();
    }
#endif

    GameEngine_TextureDestroy(&texture);
    GameEngine_VertexArrayDestroy(&vao);
    GameEngine_ShaderDestroy(&shader);
    GameEngine_BufferLayoutDestroy(&layout);
    GameEngine_IndexBufferDestroy(&ibo);
    GameEngine_VertexBufferDestroy(&vbo);
    GameEngine_RendererQuit();
    GameEngine_AppQuit();
    return 0;
}