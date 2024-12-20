#include "platform.h"

#include <stdio.h>
#include <SDL3/SDL.h>

AppDesc g_app_desc = {0};

void chess_print(char *string) {
    printf("%s\n", string);
}

void update_sdl() {
    SDL_Event sdl_event;
    while (SDL_PollEvent(&sdl_event)) {
        switch (sdl_event.type) {
            case SDL_EVENT_QUIT:
                g_app_desc.is_running = false;
                return;
        }
    }

    if (g_app_desc.update_cb) g_app_desc.update_cb(0);

    if (g_app_desc.render_cb) g_app_desc.render_cb();
}

void loop() {

}

int main(int argc, char **argv) {
    g_app_desc = chess_main(argc, argv);

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        fprintf(stderr, "SDL Failed to initialize! %s\n", SDL_GetError());
        return 1;
    }

    g_app_desc.is_running = true;
    if (g_app_desc.init_cb) g_app_desc.init_cb();

    while (g_app_desc.is_running) {
        update_sdl();
    }

    if (g_app_desc.cleanup_cb) g_app_desc.cleanup_cb();
    SDL_Quit();
    return 0;
}