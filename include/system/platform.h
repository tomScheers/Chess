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

typedef enum {
    FILE_TYPE_NONE,
    FILE_TYPE_JSON
} app_file_type_t;

typedef struct {
    app_file_type_t file_type;
    char *data;
} app_file_t;

app_file_t create_file();

app_desc_t app_main();