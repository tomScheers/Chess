#include <game_engine/app.h>
#include <game_engine/renderer.h>
#include <game_engine/gfx.h>

#include <game_engine/util/math.h>

GE_TexturedQuad_t board;
GE_Transform_t board_transform;
GE_Camera_t camera;

void Init() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    board = GameEngine_GFX_TexturedQuadCreate("data/texture/board.png");
    GameEngine_TransformInit(&board_transform);

    glm_vec3_scale(board_transform.scale, 500.f, board_transform.scale);
    board_transform.scale[2] = .1;
    camera = GameEngine_GFX_CameraOrthoCreate(1600, 900);
}

void Shutdown() {
    GameEngine_GFX_TexturedQuadDestroy(&board);
}

void Update(double dt) {
    board_transform.translation[0] = GameEngine_NormalizePosition(GE_g_input_state.mouse_x, GE_g_app.display_width, 1600);
    board_transform.translation[1] = GameEngine_NormalizePosition(GE_g_input_state.mouse_y, GE_g_app.display_height, 900);
}

void RenderPass() {
    GameEngine_GFX_TexturedQuadRender(&board, &camera, &board_transform);
}

GE_ProjectCallbacks_t Game_Entry() {
    return (GE_ProjectCallbacks_t) {
        .init = Init,
        .shutdown = Shutdown,
        .update = Update,
        .renderpass = RenderPass
    };
}