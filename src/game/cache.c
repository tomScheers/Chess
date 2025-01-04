#include <game/cache.h>

Game_Cache_t Game_g_cache = {0};

void LoadTextures() {
    Game_g_cache.debug_quad = GameEngine_GFX_TexturedQuadCreate();
    Game_g_cache.debug_quad.texture = GameEngine_TextureCreate("data/texture/debug.png");

    Game_g_cache.board_quad = GameEngine_GFX_TexturedQuadCreate();
    Game_g_cache.board_quad.texture = GameEngine_TextureCreate("data/texture/board.png");

    Game_g_cache.notch_quad = GameEngine_GFX_TexturedQuadCreate();
    Game_g_cache.notch_quad.texture = GameEngine_TextureCreate("data/texture/notch.png");

    Game_g_cache.bpawn_quad = GameEngine_GFX_TexturedQuadCreate();
    Game_g_cache.bpawn_quad.texture = GameEngine_TextureCreate("data/texture/black_pawn.png");
    Game_g_cache.wpawn_quad = GameEngine_GFX_TexturedQuadCreate();
    Game_g_cache.wpawn_quad.texture = GameEngine_TextureCreate("data/texture/white_pawn.png");

    Game_g_cache.brook_quad = GameEngine_GFX_TexturedQuadCreate();
    Game_g_cache.brook_quad.texture = GameEngine_TextureCreate("data/texture/black_rook.png");
    Game_g_cache.wrook_quad = GameEngine_GFX_TexturedQuadCreate();
    Game_g_cache.wrook_quad.texture = GameEngine_TextureCreate("data/texture/white_rook.png");

    Game_g_cache.bknight_quad = GameEngine_GFX_TexturedQuadCreate();
    Game_g_cache.bknight_quad.texture = GameEngine_TextureCreate("data/texture/black_knight.png");
    Game_g_cache.wknight_quad = GameEngine_GFX_TexturedQuadCreate();
    Game_g_cache.wknight_quad.texture = GameEngine_TextureCreate("data/texture/white_knight.png");

    Game_g_cache.bbish_quad = GameEngine_GFX_TexturedQuadCreate();
    Game_g_cache.bbish_quad.texture = GameEngine_TextureCreate("data/texture/black_bishop.png");
    Game_g_cache.wbish_quad = GameEngine_GFX_TexturedQuadCreate();
    Game_g_cache.wbish_quad.texture = GameEngine_TextureCreate("data/texture/white_bishop.png");

    Game_g_cache.bking_quad = GameEngine_GFX_TexturedQuadCreate();
    Game_g_cache.bking_quad.texture = GameEngine_TextureCreate("data/texture/black_king.png");
    Game_g_cache.wking_quad = GameEngine_GFX_TexturedQuadCreate();
    Game_g_cache.wking_quad.texture = GameEngine_TextureCreate("data/texture/white_king.png");

    Game_g_cache.bqueen_quad = GameEngine_GFX_TexturedQuadCreate();
    Game_g_cache.bqueen_quad.texture = GameEngine_TextureCreate("data/texture/black_queen.png");
    Game_g_cache.wqueen_quad = GameEngine_GFX_TexturedQuadCreate();
    Game_g_cache.wqueen_quad.texture = GameEngine_TextureCreate("data/texture/white_queen.png");
}

void UnloadTextures() {
    GameEngine_GFX_TexturedQuadDestroy(&Game_g_cache.debug_quad);

    GameEngine_GFX_TexturedQuadDestroy(&Game_g_cache.board_quad);

    GameEngine_GFX_TexturedQuadDestroy(&Game_g_cache.bpawn_quad);
    GameEngine_GFX_TexturedQuadDestroy(&Game_g_cache.wpawn_quad);

    GameEngine_GFX_TexturedQuadDestroy(&Game_g_cache.brook_quad);
    GameEngine_GFX_TexturedQuadDestroy(&Game_g_cache.wrook_quad);

    GameEngine_GFX_TexturedQuadDestroy(&Game_g_cache.bknight_quad);
    GameEngine_GFX_TexturedQuadDestroy(&Game_g_cache.wknight_quad);

    GameEngine_GFX_TexturedQuadDestroy(&Game_g_cache.bbish_quad);
    GameEngine_GFX_TexturedQuadDestroy(&Game_g_cache.wbish_quad);

    GameEngine_GFX_TexturedQuadDestroy(&Game_g_cache.bbish_quad);
    GameEngine_GFX_TexturedQuadDestroy(&Game_g_cache.wbish_quad);

    GameEngine_GFX_TexturedQuadDestroy(&Game_g_cache.bking_quad);
    GameEngine_GFX_TexturedQuadDestroy(&Game_g_cache.wking_quad);

    GameEngine_GFX_TexturedQuadDestroy(&Game_g_cache.bqueen_quad);
    GameEngine_GFX_TexturedQuadDestroy(&Game_g_cache.wqueen_quad);
}


void Game_CacheLoadAll() {
    // TODO: Load everything
    LoadTextures();
}

void Game_CacheEmpty() {
    // TODO: Delete everything
    UnloadTextures();
}