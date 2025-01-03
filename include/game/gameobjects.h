#pragma once

#include "game_engine/gfx.h"
#include <game_engine/components.h>

#include <engine/engine.h>

typedef struct {
    GE_TexturedQuad_t quad;
    GE_Transform_t transform;
} Object_Board_t;
Object_Board_t Object_Board_Create();
void Object_Board_Destroy(Object_Board_t *object);

typedef struct {
    GE_TexturedQuad_t quad;
    GE_Transform_t transform;
    float yaw;
    float pitch;
    bool accessible, held, hovering;
} Object_Piece_t;

typedef struct {
    Object_Piece_t **pieces;
} Object_PieceSet_t;

Object_PieceSet_t Object_PieceSet_Create(CE_Game *game, Object_Board_t *board);
void Object_PieceSet_Destroy(CE_Game *game, Object_PieceSet_t *object);
void Object_PieceSet_Update(Object_PieceSet_t *object);
void Object_PieceSet_Render(Object_PieceSet_t *object, GE_Camera_t *camera);