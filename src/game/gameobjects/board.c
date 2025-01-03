#include <game/gameobjects.h>

#include <game_engine/gfx.h>

#include <game/cache.h>

Object_Board_t Object_Board_Create() {
    Object_Board_t object;

    object.quad = GameEngine_GFX_TexturedQuadCreate();
    if(Game_g_cache.board_texture.file_path) {
        object.quad.texture = Game_g_cache.board_texture;
    } else {
        fprintf(stderr, "Failed to set board texture; Board not loaded in cache!");
    }

    GameEngine_TransformInit(&object.transform);

    object.transform.scale[0] = (float)900-50;
    object.transform.scale[1] = object.transform.scale[0];
    object.transform.translation[0] = ((float)1600/2)-(object.transform.scale[0]/2);
    object.transform.translation[1] = ((float)900/2)-(object.transform.scale[1]/2);
    object.transform.translation[2] = .8f;
    {
        vec3 half_scale;
        vec3 translation;
        glm_vec3_divs(object.transform.rotation_origin, 2, half_scale);
        glm_vec3_add(object.transform.translation, half_scale, translation);

        object.transform.rotation_origin[0] = translation[0];
        object.transform.rotation_origin[1] = translation[1];
    }

    return object;
}

void Object_Board_Destroy(Object_Board_t *object) {
    GameEngine_GFX_MeshDestroy(&object->quad.mesh);
    GameEngine_ShaderDestroy(&object->quad.shader);
}