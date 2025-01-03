#include <game_engine/app.h>
#include <game_engine/renderer.h>
#include <game_engine/gfx.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <cglm/cglm.h>

// For testing
#include <SDL3/SDL.h>
#include <glad/glad.h>

GE_TexturedQuad_t quad;
GE_TexturedQuad_t quad2;
GE_Camera_t camera;

void mainloop() {
    GameEngine_AppProcess();

    GameEngine_RendererClear();

    GameEngine_ShaderBind(&quad.shader);
    GameEngine_GFX_TexturedQuadRender(&quad, &camera);

    GameEngine_ShaderBind(&quad2.shader);
    GameEngine_GFX_TexturedQuadRender(&quad2, &camera);

    SDL_GL_SwapWindow(GE_g_app.display);
}

int main() {
    GameEngine_AppInit();
    GameEngine_RendererInit();

    quad = GameEngine_GFX_TexturedQuadCreate("data/image/test.png");
    camera = GameEngine_GFX_CameraOrthoCreate(1600, 900);
    quad.transform.scale[0] = 100.f;
    quad.transform.scale[1] = 100.f;

    quad2 = GameEngine_GFX_TexturedQuadCreate("data/image/test.png");
    quad2.transform.scale[0] = 100.f;
    quad2.transform.scale[1] = 100.f;
    quad2.transform.translation[0] = 100.f;
    quad2.transform.translation[1] = 100.f;

    GameEngine_ShaderDestroy(&quad2.shader);
    quad2.shader = GameEngine_ShaderCreate("data/shaders/engine/basic_debug.vert", "data/shaders/engine/basic_debug.frag");

    glClearColor(0.5f, 1.0f, 0.2f, 1.0f);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainloop, 60, 1);
#else
    while(*GameEngine_AppIsRunning()) {
        mainloop();
    }
#endif

    GameEngine_GFX_TexturedQuadDestroy(&quad);
    GameEngine_RendererQuit();
    GameEngine_AppQuit();
    return 0;
}