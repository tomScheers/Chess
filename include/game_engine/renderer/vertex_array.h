#pragma once

#include <glad/glad.h>

typedef struct {
    unsigned int id;
} GE_VertexArray_t;

GE_VertexArray_t GameEngine_VertexArrayCreate();
void GameEngine_VertexArrayDestroy(GE_VertexArray_t *vertex_array);

void GameEngine_VertexArrayBind(const GE_VertexArray_t *vertex_array);
void GameEngine_VertexArrayUnbind();