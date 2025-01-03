#include <game_engine/components.h>

void GameEngine_TransformInit(GE_Transform_t *transform) {
    if (!transform) return;
    glm_vec3_zero(transform->translation);
    glm_vec3_zero(transform->rotation);
    glm_vec3_one(transform->scale);
}