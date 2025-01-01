#include <game_engine/renderer/index_buffer.h>

#include <glad/glad.h>

GE_IndexBuffer_t GE_IndexBufferCreate(const unsigned int *data, const unsigned int count) {
    GE_IndexBuffer_t index_buffer;
    index_buffer.count = count;
    glGenBuffers(1, &index_buffer.id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer.id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    return index_buffer;
}

void GE_IndexBufferDestroy(GE_IndexBuffer_t *index_buffer) {
    glDeleteBuffers(1, &index_buffer->id);
}

void GE_IndexBufferBind(const GE_IndexBuffer_t *index_buffer) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer->id);
}

void GE_IndexBufferUnbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}