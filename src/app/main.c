#include <game_engine/app.h>
#include <game_engine/renderer.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <cglm/cglm.h>

#include <time.h>

GE_ProjectCallbacks_t callbacks;
clock_t start, end;
double dt;

void mainloop() {
    start = clock();

    GameEngine_AppProcess();
    
    if(callbacks.update) callbacks.update(dt);

    GameEngine_RendererClear();

    if(callbacks.renderpass) callbacks.renderpass();

    GameEngine_RendererSubmit();

    end = clock();

    dt = (double)(end - start) / CLOCKS_PER_SEC;
}

int main() {
    dt = 0;
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