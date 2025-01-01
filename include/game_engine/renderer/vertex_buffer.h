#pragma once

typedef struct {
    unsigned int id;
} GE_VertexBuffer_t;

GE_VertexBuffer_t GameEngine_VertexBufferCreate(const void *data, unsigned int size);
void GameEngine_VertexBufferDestroy(GE_VertexBuffer_t *vertex_buffer);

void GameEngine_VertexBufferBind(const GE_VertexBuffer_t *vertex_buffer);
void GameEngine_VertexBufferUnbind();