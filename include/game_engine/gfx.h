#pragma once
#include <game_engine/renderer.h>
#include <cglm/cglm.h>

typedef struct {
    GE_VertexArray_t vao;
    GE_VertexBuffer_t vbo;
    GE_IndexBuffer_t ibo;
    GE_BufferLayout_t layout;
    float *vertices;
    unsigned int *indices, vertex_count, index_count;
} GE_Mesh_t;

typedef struct {
    vec3 translation;
    vec3 rotation;
    vec3 scale;
} GE_Transform_t;

typedef struct {
    GE_Mesh_t mesh;
    GE_Shader_t shader;
    GE_Texture_t texture;
    GE_Transform_t transform;
} GE_TexturedQuad_t;

typedef struct {
    GE_Shader_t shader;
    GE_Transform_t transform;
    mat4 view, projection;
} GE_Camera_t;

GE_TexturedQuad_t GameEngine_GFX_TexturedQuadCreate(const char *texture_file_path);
void GameEngine_GFX_TexturedQuadDestroy(GE_TexturedQuad_t *quad);

void GameEngine_GFX_TexturedQuadRender(GE_TexturedQuad_t *quad, GE_Camera_t *camera);

GE_Camera_t GameEngine_GFX_CameraOrthoCreate(int width, int height);
void GameEngine_GFX_CameraOrthoSetSize(GE_Camera_t *camera, int width, int height);