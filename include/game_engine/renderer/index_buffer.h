#pragma once

typedef struct {
    unsigned int id;
    unsigned int count;
} GE_IndexBuffer_t;

GE_IndexBuffer_t GameEngine_IndexBufferCreate(const unsigned int *data, const unsigned int count);
void GameEngine_IndexBufferDestroy(GE_IndexBuffer_t *index_buffer);

void GameEngine_IndexBufferBind(const GE_IndexBuffer_t *index_buffer);
void GameEngine_IndexBufferUnbind();