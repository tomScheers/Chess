#include <system/platform.h>
app_desc_t g_app_desc = {0};

#define SOKOL_IMPL
#define SOKOL_GLCORE
#include <sokol_gfx.h>
#include <SDL3/SDL.h>

void handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                g_app_desc.is_running = false;
        }
    }
}

void render() {
    SDL_GL_SwapWindow(g_app_desc.surface);
}

void main_loop() {
    handle_events();
    render();
}

int main() {
    g_app_desc = app_main();

    SDL_Init(SDL_INIT_VIDEO);
    g_app_desc.is_running = true;

    g_app_desc.surface = SDL_CreateWindow(g_app_desc.title, 800, 600, SDL_WINDOW_OPENGL);
    g_app_desc.backend = SDL_GL_CreateContext(g_app_desc.surface);
    SDL_GL_SetSwapInterval(!g_app_desc.vsync_disabled);

    while (g_app_desc.is_running) {
        main_loop();
    }

    SDL_GL_DestroyContext(g_app_desc.backend);
    SDL_DestroyWindow(g_app_desc.surface);
    SDL_Quit();
    return 0;
}