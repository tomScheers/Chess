#include <game_engine/renderer/vertex_buffer.h>

#include <glad/glad.h>

GE_VertexBuffer_t GE_VertexBufferCreate(const void *data, const unsigned int size) {
    GE_VertexBuffer_t vertex_buffer;
    glGenBuffers(1, &vertex_buffer.id);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer.id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    return vertex_buffer;
}

void GE_VertexBufferDestroy(GE_VertexBuffer_t *vertex_buffer) {
    glDeleteBuffers(1, &vertex_buffer->id);
}

void GE_VertexBufferBind(const GE_VertexBuffer_t *vertex_buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->id);
}

void GE_VertexBufferUnbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}