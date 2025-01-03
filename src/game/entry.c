#include <game_engine/app.h>
#include <game_engine/renderer.h>
#include <game_engine/gfx.h>

#include <game_engine/util/math.h>

#include "textures.h"

typedef struct {
    GE_TexturedQuad_t quad;
    GE_Transform_t transform;
} Game_BoardObject_t;

typedef struct {
    int coord_width, coord_height;
} Game_LayoutInfo_t;


Game_BoardObject_t board;
Game_LayoutInfo_t layout;
GE_Camera_t camera;

void Init() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    layout = (Game_LayoutInfo_t) {
        .coord_width = 1600,
        .coord_height = 900
    };

    camera = GameEngine_GFX_CameraOrthoCreate(layout.coord_width, layout.coord_height);
    Game_LoadTextures();

    board.quad = GameEngine_GFX_TexturedQuadCreate();
    board.quad.texture = g_texture_cache.board_texture;

    GameEngine_TransformInit(&board.transform);

    // Center and scale board
    board.transform.scale[0] = (float)layout.coord_height-50;
    board.transform.scale[1] = board.transform.scale[0];
    board.transform.translation[0] = ((float)layout.coord_width/2)-(board.transform.scale[0]/2);
    board.transform.translation[1] = ((float)layout.coord_height/2)-(board.transform.scale[1]/2);
}

void Shutdown() {
}

void Update(double dt) {
}

void RenderPass() {
    GameEngine_ShaderBind(&board.quad.shader);
    GameEngine_GFX_TexturedQuadRender(&board.quad, &camera, &board.transform);
}

GE_ProjectCallbacks_t Game_Entry() {
    return (GE_ProjectCallbacks_t) {
        .init = Init,
        .shutdown = Shutdown,
        .update = Update,
        .renderpass = RenderPass
    };
}