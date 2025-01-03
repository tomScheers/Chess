#pragma once

#include <game_engine/renderer/texture.h>

typedef struct {
    GE_Texture_t board_texture;
} Game_Cache_t;
extern Game_Cache_t Game_g_cache;

void Game_CacheLoadAll();
void Game_CacheEmpty();