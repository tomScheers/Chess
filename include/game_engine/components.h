#pragma once

#include <cglm/cglm.h>

typedef struct {
    vec3 translation;
    vec3 rotation, rotation_origin;
    vec3 scale;
} GE_Transform_t;

void GameEngine_TransformInit(GE_Transform_t *transform);