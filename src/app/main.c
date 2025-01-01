#include <game_engine/app.h>
#include <game_engine/renderer.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

void mainloop() {
    GameEngine_AppProcess();
}

int main() {
    GameEngine_AppInit();
    GameEngine_RendererInit();
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainloop, 60, 1);
#else
    while(*GameEngine_AppIsRunning()) {
        mainloop();
    }
#endif
    GameEngine_RendererQuit();
    GameEngine_AppQuit();
    return 0;
}