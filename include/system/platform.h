#pragma once

#include <stdbool.h>

typedef struct {
    char *title;
    bool is_running;
    bool vsync_disabled;

    void *surface;
    void *backend;
} app_desc_t;
extern app_desc_t g_app_desc;

app_desc_t app_main();