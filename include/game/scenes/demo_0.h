#pragma once

#include "SDL3/SDL_scancode.h"
#include "game/scenes.h"
#include "game_engine/app.h"
#include <stdio.h>

#include <game/gameobjects.h>
#include <game/cache.h>

#include <game_engine/util/math.h>

GE_Camera_t camera;

Object_Board_t board;
Object_Cursor_t cursor;

Object_PieceSet_t pieces;

void Game_Scene_Demo0_Init() {
    printf("Demo 0 initialized\n");
    board = Object_Board_Create();
    camera = GameEngine_GFX_CameraOrthoCreate(1600, 900);
    pieces = Object_PieceSet_Create(&board);

}

void Game_Scene_Demo0_Shutdown() {
    Object_PieceSet_Destroy(&pieces);
}

void Game_Scene_Demo0_Update(double dt) {
    if(GE_g_input_state.keys[SDL_SCANCODE_R]) {
        Game_SceneLoad(GAME_SCENE_DEMO_0);
    }

    Object_PieceSet_Update(&pieces, &board, &cursor, dt);
}

void Game_Scene_Demo0_Render() {
    GameEngine_ShaderBind(&board.quad->shader);
    GameEngine_TextureBind(&board.quad->texture, 0);
    GameEngine_GFX_TexturedQuadRender(board.quad, &camera, &board.transform);

    Object_PieceSet_Render(&pieces, &cursor, &camera);
}