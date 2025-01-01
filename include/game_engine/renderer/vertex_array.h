#pragma once

#include <glad/glad.h>

typedef struct {
    unsigned int id;
} GE_VertexArray_t;

inline GE_VertexArray_t GameEngine_VertexArrayCreate() {
    GE_VertexArray_t vertex_array;
    glGenVertexArrays(1, &vertex_array.id);
    return vertex_array;
}
inline void GameEngine_VertexArrayDestroy(GE_VertexArray_t *vertex_array) {
    glDeleteVertexArrays(1, &vertex_array->id);
}

inline void GameEngine_VertexArrayBind(const GE_VertexArray_t *vertex_array) {
    glBindVertexArray(vertex_array->id);
}

inline void GameEngine_VertexArrayUnbind() {
    glBindVertexArray(0);
}