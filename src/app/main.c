#include <game_engine/app.h>
#include <game_engine/renderer.h>
#include <game_engine/gfx.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <cglm/cglm.h>

GE_ProjectCallbacks_t callbacks;

void mainloop() {
    GameEngine_AppProcess();
    
    // TODO: Calculate delta time

    if(callbacks.update) callbacks.update(0);

    GameEngine_RendererClear();

    if(callbacks.renderpass) callbacks.renderpass();

    GameEngine_RendererSubmit();
}

int main() {
    GameEngine_AppInit();
    GameEngine_RendererInit();
    callbacks = Game_Entry();

    if(callbacks.init) callbacks.init();

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainloop, 60, 1);
#else
    while(*GameEngine_AppIsRunning()) {
        mainloop();
    }
#endif

    if(callbacks.shutdown) callbacks.shutdown();
    GameEngine_RendererQuit();
    GameEngine_AppQuit();
    return 0;
}