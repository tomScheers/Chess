#include <game_engine/app.h>

#include <game/cache.h>
#include <game/scenes.h>

#include "glad/glad.h"

Game_SceneState_t Game_g_scene_state = {0};

void Init() {
    glClearColor(.15f, .05f, .1f, 1.f);
    Game_CacheLoadAll();
    Game_SceneLoad(GAME_SCENE_DEMO_0);
}

void Shutdown() {
    if(Game_g_scene_state.scene_shutdown_cb) Game_g_scene_state.scene_shutdown_cb();
    Game_CacheEmpty();
}

void Update(double dt) {
    if(Game_g_scene_state.scene_update_cb) Game_g_scene_state.scene_update_cb(dt);
}

void Renderpass() {
    if(Game_g_scene_state.scene_render_cb) Game_g_scene_state.scene_render_cb();
}

GE_ProjectCallbacks_t Game_Entry() {
    return (GE_ProjectCallbacks_t) {
        .init = Init,
        .shutdown = Shutdown,
        .update = Update,
        .renderpass = Renderpass
    };
}