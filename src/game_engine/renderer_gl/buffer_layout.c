#include <game_engine/renderer/buffer_layout.h>
#include <glad/glad.h>

#include <stdlib.h>

GE_BufferLayout_t GameEngine_BufferLayoutCreate() {
    GE_BufferLayout_t layout;
    layout.attributes = NULL;
    layout.attribute_count = 0;
    layout.stride = 0;
    return layout;
}

void GameEngine_BufferLayoutDestroy(GE_BufferLayout_t *layout) {
    free(layout->attributes);
    layout->attributes = NULL;
    layout->attribute_count = 0;
    layout->stride = 0;
}

void GameEngine_BufferLayoutAddAttribute(GE_BufferLayout_t *layout, unsigned int type, unsigned int count, unsigned char normalized) {
    layout->attributes = realloc(layout->attributes, (layout->attribute_count + 1) * sizeof(GE_BufferAttribute_t));

    unsigned int size;
    switch (type) {
        case GL_FLOAT: size = sizeof(float); break;
        case GL_INT:   size = sizeof(int); break;
        default:       size = 0; 
    }

    layout->attributes[layout->attribute_count].type = type;
    layout->attributes[layout->attribute_count].count = count;
    layout->attributes[layout->attribute_count].normalized = normalized;
    layout->attributes[layout->attribute_count].offset = layout->stride;
    layout->stride += size * count;

    layout->attribute_count++;
}

void GameEngine_BufferLayoutBind(const GE_BufferLayout_t *layout) {
    unsigned int offset = 0;
    for (unsigned int i = 0; i < layout->attribute_count; i++) {
        const GE_BufferAttribute_t* attr = &layout->attributes[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, attr->count, attr->type, attr->normalized, layout->stride, (const void*)(uintptr_t)attr->offset);
    }
}