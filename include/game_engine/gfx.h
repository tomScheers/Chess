#pragma once
#include <game_engine/renderer.h>

#include <game_engine/types.h>

typedef struct {
    GE_VertexArray_t vao;
    GE_VertexBuffer_t vbo;
    GE_IndexBuffer_t ibo;
    GE_BufferLayout_t layout;
    float *vertices;
    unsigned int *indices, vertex_count, index_count;
} GE_Mesh_t;

typedef struct {
    GE_Mesh_t mesh;
    GE_Shader_t shader;
    GE_Texture_t texture;
} GE_TexturedQuad_t;

typedef struct {
    GE_Shader_t shader;
    GE_Transform_t transform;
    int width, height;
    mat4 view, projection;
} GE_Camera_t;

GE_TexturedQuad_t GameEngine_GFX_TexturedQuadCreate();

void GameEngine_GFX_TexturedQuadDestroy(GE_TexturedQuad_t *quad);

void GameEngine_GFX_TexturedQuadRender(GE_TexturedQuad_t *quad, GE_Camera_t *camera, GE_Transform_t *transform);

GE_Camera_t GameEngine_GFX_CameraOrthoCreate(int width, int height);
void GameEngine_GFX_CameraOrthoSetSize(GE_Camera_t *camera, int width, int height);