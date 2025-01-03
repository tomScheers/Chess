#pragma once

#include <game/scenes.h>

typedef struct {
    void (*scene_shutdown_cb)(void), (*scene_update_cb)(double dt), (*scene_render_cb)(void);
} Game_State_t;
Game_State_t Game_g_state;

void Game_SceneLoad(Game_Scene_e scene) {
    if(Game_g_state.scene_shutdown_cb) Game_g_state.scene_shutdown_cb();

    switch(scene) {
        case GAME_SCENE_TEST:
            Game_Scene_Test_Init();
            Game_g_state.scene_shutdown_cb = Game_Scene_Test_Shutdown;
            Game_g_state.scene_update_cb = Game_Scene_Test_Update;
            Game_g_state.scene_render_cb = Game_Scene_Test_Render;
        default:
            break;
    }
}