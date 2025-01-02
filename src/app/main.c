#include <game_engine/app.h>
#include <game_engine/renderer.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <cglm/cglm.h>

// For testing
#include <SDL3/SDL.h>
#include <glad/glad.h>

float vertices[] = {
    0.0f,   0.0f,   0.0f, 0.0f,
    100.0f, 0.0f,   1.0f, 0.0f,
    100.0f, 100.0f, 1.0f, 1.0f,
    0.0f,   100.0f, 0.0f, 1.0f
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

mat4 model = GLM_MAT4_IDENTITY_INIT;
mat4 view = GLM_MAT4_IDENTITY_INIT;
mat4 proj = GLM_MAT4_IDENTITY_INIT;

mat4 mvp = GLM_MAT4_IDENTITY_INIT;

void mainloop() {
    GameEngine_AppProcess();

    glm_mat4_identity(model);
    glm_translate(model, (vec3){0.0f, 0.0f, 0.0f});

    glm_mat4_identity(mvp);
    glm_mat4_mul(proj, view, mvp);
    glm_mat4_mul(mvp, model, mvp);

    GameEngine_RendererClear();

    GameEngine_ShaderBind(&shader);
    GameEngine_ShaderSetUniformMat4(&shader, "u_MVP", (float *)&mvp);
    GameEngine_HashMapPrint(shader.uniform_cache);
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

    glm_translate(model, (vec3){300.0f, 300.0f, 0.0f});
    glm_translate(view, (vec3){0.0f, 0.0f, 0.0f});
    glm_ortho(0.f, 1920.f, 0.f, 1080.f, -1.0, 100.0f, proj);

    shader = GameEngine_ShaderCreate("data/shaders/engine/textured.vert", "data/shaders/engine/textured.frag");
    GameEngine_ShaderBind(&shader);
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