#pragma once

#include "scenes/demo_0.h"

typedef enum {
    GAME_SCENE_DEMO_0
} Game_Scene_e;

typedef struct {
    void (*scene_shutdown_cb)(void), (*scene_update_cb)(double dt), (*scene_render_cb)(void);
} Game_SceneState_t;
extern Game_SceneState_t Game_g_scene_state;

void Game_SceneLoad(Game_Scene_e scene) {
    if(Game_g_scene_state.scene_shutdown_cb) Game_g_scene_state.scene_shutdown_cb();

    switch(scene) {
        case GAME_SCENE_DEMO_0:
            Game_Scene_Demo0_Init();
            Game_g_scene_state.scene_shutdown_cb = Game_Scene_Demo0_Shutdown;
            Game_g_scene_state.scene_update_cb = Game_Scene_Demo0_Update;
            Game_g_scene_state.scene_render_cb = Game_Scene_Demo0_Render;
        default:
            break;
    }
}