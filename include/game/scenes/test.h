#pragma once

#include <game/scenes.h>
#include <game/cache.h>

#include <game_engine/gfx.h>

#include <game/gameobjects.h>

#include <stdio.h>
#include <cglm/cglm.h>
#include <time.h>

GE_Camera_t camera;
Object_Board_t board;

float accumulated_time = 0.0f;

float amplitude = 100.0f; // Max displacement
float frequency = 2.0f;  // 2 cycles per second
float base_position;

float start_time;

void Game_Scene_Test_Init() {
    fprintf(stdout, "Test scene initialized\n");
    camera = GameEngine_GFX_CameraOrthoCreate(1600, 900);
    board = Object_Board_Create();
    base_position = board.transform.translation[0];
    start_time = (double)clock() / CLOCKS_PER_SEC;
}

void Game_Scene_Test_Shutdown() {
    Object_Board_Destroy(&board);
}

void Game_Scene_Test_Update(double dt) {
    board.transform.translation[0] = amplitude * sin(2.0f * CGLM_PI * frequency * accumulated_time) + base_position;

    // board.transform.translation[0] = sin(time(0));

    accumulated_time += dt;
}

void Game_Scene_Test_Render() {
    GameEngine_GFX_TexturedQuadRender(&board.quad, &camera, &board.transform);
}