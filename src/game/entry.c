#include <game_engine/app.h>
#include <game_engine/renderer.h>
#include <game_engine/gfx.h>

GE_TexturedQuad_t quad;
GE_Camera_t camera;

void init() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    quad = GameEngine_GFX_TexturedQuadCreate("data/image/test.png");
    quad.transform.scale[0] = 100.f;
    quad.transform.scale[1] = 100.f;
    camera = GameEngine_GFX_CameraOrthoCreate(1600, 900);
}

void shutdown() {
    GameEngine_GFX_TexturedQuadDestroy(&quad);
}

void update(double dt) {

}

void renderpass() {
    GameEngine_GFX_TexturedQuadRender(&quad, &camera);
}

GE_ProjectCallbacks_t Game_Entry() {
    return (GE_ProjectCallbacks_t) {
        .init = init,
        .shutdown = shutdown,
        .update = update,
        .renderpass = renderpass
    };
}