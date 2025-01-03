#include <game_engine/renderer/vertex_buffer.h>

#include <glad/glad.h>

#include <stdio.h>

GE_VertexBuffer_t GameEngine_VertexBufferCreate(const void *data, const unsigned int size) {
    GE_VertexBuffer_t vertex_buffer = {0};

    if (!data || size == 0) {
        fprintf(stderr, "Error: Invalid data or size for vertex buffer creation.\n");
        return vertex_buffer;
    }

    glGenBuffers(1, &vertex_buffer.id);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer.id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    return vertex_buffer;
}

void GameEngine_VertexBufferDestroy(GE_VertexBuffer_t *vertex_buffer) {
    glDeleteBuffers(1, &vertex_buffer->id);
    vertex_buffer->id = 0;
}

void GameEngine_VertexBufferBind(const GE_VertexBuffer_t *vertex_buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->id);
}

void GameEngine_VertexBufferUnbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}