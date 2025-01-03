#pragma once

#include "game_engine/gfx.h"
#include <game_engine/components.h>

typedef struct {
    GE_TexturedQuad_t quad;
    GE_Transform_t transform;
} Object_Board_t;
Object_Board_t Object_Board_Create();
void Object_Board_Destroy(Object_Board_t *object);