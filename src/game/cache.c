#include <game/cache.h>

Game_Cache_t Game_g_cache = {0};

void LoadTextures() {
    Game_g_cache.debug_texture = GameEngine_TextureCreate("data/texture/debug.png");
    Game_g_cache.board_texture = GameEngine_TextureCreate("data/texture/board.png");

    Game_g_cache.bpawn_texture = GameEngine_TextureCreate("data/texture/black_pawn.png");
    Game_g_cache.wpawn_texture = GameEngine_TextureCreate("data/texture/white_pawn.png");

    Game_g_cache.brook_texture = GameEngine_TextureCreate("data/texture/black_rook.png");
    Game_g_cache.wrook_texture = GameEngine_TextureCreate("data/texture/white_rook.png");

    Game_g_cache.bknight_texture = GameEngine_TextureCreate("data/texture/black_knight.png");
    Game_g_cache.wknight_texture = GameEngine_TextureCreate("data/texture/white_knight.png");

    Game_g_cache.bbish_texture = GameEngine_TextureCreate("data/texture/black_bishop.png");
    Game_g_cache.wbish_texture = GameEngine_TextureCreate("data/texture/white_bishop.png");

    Game_g_cache.bking_texture = GameEngine_TextureCreate("data/texture/black_king.png");
    Game_g_cache.wking_texture = GameEngine_TextureCreate("data/texture/white_king.png");

    Game_g_cache.bqueen_texture = GameEngine_TextureCreate("data/texture/black_queen.png");
    Game_g_cache.wqueen_texture = GameEngine_TextureCreate("data/texture/white_queen.png");
}

void UnloadTextures() {
    GameEngine_TextureDestroy(&Game_g_cache.debug_texture);
    GameEngine_TextureDestroy(&Game_g_cache.board_texture);

    GameEngine_TextureDestroy(&Game_g_cache.bpawn_texture);
    GameEngine_TextureDestroy(&Game_g_cache.wpawn_texture);

    GameEngine_TextureDestroy(&Game_g_cache.brook_texture);
    GameEngine_TextureDestroy(&Game_g_cache.wrook_texture);
}

void Game_CacheLoadAll() {
    // TODO: Load everything
    LoadTextures();
}

void Game_CacheEmpty() {
    // TODO: Delete everything
    UnloadTextures();
}