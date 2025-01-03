#include <game/cache.h>

Game_Cache_t Game_g_cache = {0};

void Game_CacheLoadAll() {
    // TODO: Load everything
    Game_g_cache.board_texture = GameEngine_TextureCreate("data/texture/board.png");
}

void Game_CacheEmpty() {
    // TODO: Delete everything
    GameEngine_TextureDestroy(&Game_g_cache.board_texture);
}