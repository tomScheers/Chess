#include "textures.h"

Game_TextureCache_t g_texture_cache = {0};

void Game_LoadTextures() {
    g_texture_cache.board_texture = GameEngine_TextureCreate("data/texture/board.png");
}