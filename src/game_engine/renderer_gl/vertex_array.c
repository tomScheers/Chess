#include <game_engine/renderer/vertex_array.h>

#include <glad/glad.h>

GE_VertexArray_t GameEngine_VertexArrayCreate() {
    GE_VertexArray_t vertex_array;
    glGenVertexArrays(1, &vertex_array.id);
    return vertex_array;
}

void GameEngine_VertexArrayDestroy(GE_VertexArray_t *vertex_array) {
    glDeleteVertexArrays(1, &vertex_array->id);
}

void GameEngine_VertexArrayBind(const GE_VertexArray_t *vertex_array) {
    glBindVertexArray(vertex_array->id);
}

void GameEngine_VertexArrayUnbind() {
    glBindVertexArray(0);
}