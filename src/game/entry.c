#include <game_engine/app.h>

#include <game/cache.h>
#include <game/state.h>

void Init() {
    Game_CacheLoadAll();
    Game_SceneLoad(GAME_SCENE_TEST);
}

void Shutdown() {
    if(Game_g_state.scene_shutdown_cb) Game_g_state.scene_shutdown_cb();
    Game_CacheEmpty();
}

void Update(double dt) {
    if(Game_g_state.scene_update_cb) Game_g_state.scene_update_cb(dt);
}

void Renderpass() {
    if(Game_g_state.scene_render_cb) Game_g_state.scene_render_cb();
}

GE_ProjectCallbacks_t Game_Entry() {
    return (GE_ProjectCallbacks_t) {
        .init = Init,
        .shutdown = Shutdown,
        .update = Update,
        .renderpass = Renderpass
    };
}