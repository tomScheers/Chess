#pragma once

#include <stdbool.h>

#include <cglm/cglm.h>

typedef struct {
    char *title;
    void (*update_cb)(float dt);
    void (*render_cb)(void);
    void (*init_cb)(void);
    void (*cleanup_cb)(void);

    bool is_running;
} AppDesc;
extern AppDesc g_app_desc;

typedef struct {
    char *vs;
    char *fs;
} Shader;

typedef struct {
    vec4 points[3];
    Shader shader;
} Quad;

AppDesc chess_main(int argc, char **argv);

// for IMPL

void chess_quad_render();
void chess_sprite_render();
