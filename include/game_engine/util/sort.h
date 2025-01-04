#pragma once

#include "SDL3/SDL_stdinc.h"
#include <math.h>
#include <glad/glad.h>
#include <game_engine/components.h>
#include <game_engine/gfx.h>

float distance_from_camera(const GE_Transform_t *obj, const GE_Camera_t *camera) {
    return sqrtf(
        (obj->translation[0] - camera->transform.translation[0]) * (obj->translation[0] - camera->transform.translation[0]) +
        (obj->translation[1] - camera->transform.translation[1]) * (obj->translation[1] - camera->transform.translation[1]) +
        (obj->translation[2] - camera->transform.translation[2]) * (obj->translation[2] - camera->transform.translation[2])
    );
}

int compare_distance(void *camera, const void *a, const void *b) {
    float dist_a = distance_from_camera((GE_Transform_t *)a, (GE_Camera_t *)camera);
    float dist_b = distance_from_camera((GE_Transform_t *)b, (GE_Camera_t *)camera);
    
    if (dist_a < dist_b) return 1;  // Farthest first
    if (dist_a > dist_b) return -1; // Closest first
    return 0;
}

void sort_objects_by_distance(GE_Transform_t *transforms, int numObjects, GE_Camera_t *camera) {
    SDL_qsort_r(transforms, numObjects, sizeof(GE_Transform_t), compare_distance, camera);
}

