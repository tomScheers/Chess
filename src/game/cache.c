#include <game/cache.h>

Game_Cache_t Game_g_cache = {0};

void LoadTextures() {
    Game_g_cache.debug_texture = GameEngine_TextureCreate("data/texture/debug.png");
    Game_g_cache.board_texture = GameEngine_TextureCreate("data/texture/board.png");

    Game_g_cache.bpawn_texture = GameEngine_TextureCreate("data/texture/black_pawn.png");
    Game_g_cache.wpawn_texture = GameEngine_TextureCreate("data/texture/white_pawn.png");
}

void Game_CacheLoadAll() {
    // TODO: Load everything
    LoadTextures();
}

void Game_CacheEmpty() {
    // TODO: Delete everything
    GameEngine_TextureDestroy(&Game_g_cache.debug_texture);
    GameEngine_TextureDestroy(&Game_g_cache.board_texture);
}