#pragma once

typedef struct {
    unsigned int type;    
    unsigned int count;   
    unsigned char normalized; 
    unsigned int offset;  
} GE_BufferAttribute_t;

typedef struct {
    GE_BufferAttribute_t* attributes; 
    unsigned int attribute_count; 
    unsigned int stride;         
} GE_BufferLayout_t;

GE_BufferLayout_t GameEngine_BufferLayoutCreate();
void GameEngine_BufferLayoutDestroy(GE_BufferLayout_t *layout);

void GameEngine_BufferLayoutAddAttribute(GE_BufferLayout_t *layout, unsigned int type, unsigned int count, unsigned char normalized);
void GameEngine_BufferLayoutBind(const GE_BufferLayout_t *layout);