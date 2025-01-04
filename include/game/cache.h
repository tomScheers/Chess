#pragma once

#include <game_engine/renderer/texture.h>
#include <game_engine/gfx.h>

typedef struct {
    GE_TexturedQuad_t debug_quad;
    GE_TexturedQuad_t board_quad;
    GE_TexturedQuad_t notch_quad;
    GE_TexturedQuad_t bpawn_quad, wpawn_quad;
    GE_TexturedQuad_t brook_quad, wrook_quad;
    GE_TexturedQuad_t bknight_quad, wknight_quad;
    GE_TexturedQuad_t bbish_quad, wbish_quad;
    GE_TexturedQuad_t bking_quad, wking_quad;
    GE_TexturedQuad_t bqueen_quad, wqueen_quad;
} Game_Cache_t;
extern Game_Cache_t Game_g_cache;

void Game_CacheLoadAll();
void Game_CacheEmpty();