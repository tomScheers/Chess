#pragma once

#include <game_engine/renderer/texture.h>

typedef struct {
    GE_Texture_t debug_texture;
    GE_Texture_t board_texture;
    GE_Texture_t bpawn_texture, wpawn_texture;
    GE_Texture_t brook_texture, wrook_texture;
    GE_Texture_t bknight_texture, wknight_texture;
    GE_Texture_t bbish_texture, wbish_texture;
    GE_Texture_t bking_texture, wking_texture;
    GE_Texture_t bqueen_texture, wqueen_texture;
} Game_Cache_t;
extern Game_Cache_t Game_g_cache;

void Game_CacheLoadAll();
void Game_CacheEmpty();