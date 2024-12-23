#pragma once

#include <stdbool.h>

typedef struct {
    bool vsync_disabled;
} user_config_t;

void set_user_config_defaults(user_config_t *config);
user_config_t load_or_create_user_config(const char *filename);