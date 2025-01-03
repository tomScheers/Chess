#pragma once

#include <game_engine/app.h>
#include <game_engine/renderer.h>
#include <game_engine/gfx.h>

typedef struct {
    GE_Texture_t board_texture;
} Game_TextureCache_t;
extern Game_TextureCache_t g_texture_cache;

void Game_LoadTextures();