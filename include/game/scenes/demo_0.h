#pragma once

#include <stdio.h>

#include <game/gameobjects.h>
#include <game/cache.h>

Object_Board_t board;
GE_Camera_t camera;

void Game_Scene_Demo0_Init() {
    printf("Demo 0 initialized\n");
    board = Object_Board_Create();
    camera = GameEngine_GFX_CameraOrthoCreate(1600, 900);
}

void Game_Scene_Demo0_Shutdown() {
    Object_Board_Destroy(&board);
}

void Game_Scene_Demo0_Update(double dt) {

}

void Game_Scene_Demo0_Render() {
    GameEngine_ShaderBind(&board.quad.shader);
    GameEngine_TextureBind(&board.quad.texture, 0);
    GameEngine_GFX_TexturedQuadRender(&board.quad, &camera, &board.transform);
}