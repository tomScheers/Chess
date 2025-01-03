#include <game_engine/app.h>
#include <game_engine/renderer.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <cglm/cglm.h>
#include <SDL3/SDL_timer.h>

GE_ProjectCallbacks_t callbacks;
Uint32 last_time;
Uint32 current_time;
float delta_time;

void mainloop() {
    GameEngine_AppProcess();

    current_time = SDL_GetTicks();
    delta_time = (current_time - last_time) / 1000.0f;
    last_time = current_time;
    
    if(callbacks.update) callbacks.update(delta_time);

    GameEngine_RendererClear();

    if(callbacks.renderpass) callbacks.renderpass();

    GameEngine_RendererSubmit();
}

int main() {
    last_time = SDL_GetTicks();
    delta_time = 0;
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