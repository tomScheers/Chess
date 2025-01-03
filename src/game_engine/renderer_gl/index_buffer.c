#include <game_engine/renderer/index_buffer.h>

#include <glad/glad.h>

#include <stdio.h>

GE_IndexBuffer_t GameEngine_IndexBufferCreate(const unsigned int *data, const unsigned int count) {
    GE_IndexBuffer_t index_buffer = {0};
    
    if (!data || count == 0) {
        fprintf(stderr, "Error: Invalid data or count for index buffer creation.\n");
        return index_buffer;
    }

    index_buffer.count = count;

    glGenBuffers(1, &index_buffer.id);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer.id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);

    return index_buffer;
}

void GameEngine_IndexBufferDestroy(GE_IndexBuffer_t *index_buffer) {
    glDeleteBuffers(1, &index_buffer->id);
    index_buffer->id = 0;
}

void GameEngine_IndexBufferBind(const GE_IndexBuffer_t *index_buffer) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer->id);
}

void GameEngine_IndexBufferUnbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
