#include <game_engine/gfx.h>
#include <game_engine/renderer.h>

#include <cglm/cglm.h>

#include <string.h>
#include <stdlib.h>

void InitializeTransform(GE_Transform_t *transform) {
    if (!transform) return;
    glm_vec3_zero(transform->translation);
    glm_vec3_zero(transform->rotation);
    glm_vec3_one(transform->scale);
}

void GameEngine_GFX_MeshDestroy(GE_Mesh_t *mesh) {
    if(mesh) {
        if(mesh->vertices) {
            free(mesh->vertices);
            mesh->vertices = NULL;
        }

        if(mesh->indices) {
            free(mesh->indices);
            mesh->indices = NULL;
        }

        GameEngine_VertexArrayDestroy(&mesh->vao);
        GameEngine_IndexBufferDestroy(&mesh->ibo);
        GameEngine_VertexBufferDestroy(&mesh->vbo);
        GameEngine_BufferLayoutDestroy(&mesh->layout);
    }
}

GE_TexturedQuad_t GameEngine_GFX_TexturedQuadCreate(const char *texture_file_path) {
    GE_TexturedQuad_t quad = {0};

    float vertices[] = {
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    quad.mesh.vertices = (float *)malloc(sizeof(vertices));
    if (!quad.mesh.vertices) {
        return quad;
    }

    quad.mesh.indices = (unsigned int *)malloc(sizeof(indices));
    if (!quad.mesh.indices) {
        free(quad.mesh.vertices);
        quad.mesh.vertices = NULL;
        return quad;
    }

    memcpy(quad.mesh.vertices, vertices, sizeof(vertices));
    memcpy(quad.mesh.indices, indices, sizeof(indices));

    quad.mesh.vao = GameEngine_VertexArrayCreate();
    if (quad.mesh.vao.id == 0) {
        free(quad.mesh.vertices);
        free(quad.mesh.indices);
        quad.mesh.vertices = NULL;
        quad.mesh.indices = NULL;
        return quad;
    }

    GameEngine_VertexArrayBind(&quad.mesh.vao);

    quad.mesh.vbo = GameEngine_VertexBufferCreate(quad.mesh.vertices, sizeof(vertices));
    quad.mesh.ibo = GameEngine_IndexBufferCreate(quad.mesh.indices, 6);

    quad.mesh.layout = GameEngine_BufferLayoutCreate();
    GameEngine_BufferLayoutAddAttribute(&quad.mesh.layout, GL_FLOAT, 3, GL_FALSE);
    GameEngine_BufferLayoutAddAttribute(&quad.mesh.layout, GL_FLOAT, 2, GL_FALSE);
    GameEngine_BufferLayoutBind(&quad.mesh.layout);

    quad.shader = GameEngine_ShaderCreate("data/shaders/engine/basic_tq.vert", "data/shaders/engine/basic_tq.frag");
    quad.texture = GameEngine_TextureCreate(texture_file_path);

    InitializeTransform(&quad.transform);

    return quad;
}

void GameEngine_GFX_TexturedQuadDestroy(GE_TexturedQuad_t *quad) {
    if (quad) {
        GameEngine_GFX_MeshDestroy(&quad->mesh);
        GameEngine_ShaderDestroy(&quad->shader);
        GameEngine_TextureDestroy(&quad->texture);

        memset(quad, 0, sizeof(GE_TexturedQuad_t));
    }
}

void GameEngine_GFX_TexturedQuadRender(GE_TexturedQuad_t *quad, GE_Camera_t *camera) {
    if (!quad || !camera) return;

    mat4 mvp, model;
    glm_mat4_identity(mvp);
    glm_mat4_identity(model);

    glm_translate(model, (float *)quad->transform.translation);
    glm_rotate(model, quad->transform.rotation[0], (vec3){1.0f, 0.0f, 0.0f});
    glm_rotate(model, quad->transform.rotation[1], (vec3){0.0f, 1.0f, 0.0f});
    glm_rotate(model, quad->transform.rotation[2], (vec3){0.0f, 0.0f, 1.0f});
    glm_scale(model, (float *)quad->transform.scale);

    glm_mat4_mul(camera->projection, camera->view, mvp);
    glm_mat4_mul(mvp, model, mvp);

    GameEngine_VertexArrayBind(&quad->mesh.vao);
    GameEngine_IndexBufferBind(&quad->mesh.ibo);
    GameEngine_TextureBind(&quad->texture, 0);

    GameEngine_ShaderSetUniformInt(&quad->shader, "u_Texture", 0);
    GameEngine_ShaderSetUniformMat4(&quad->shader, "u_MVP", (float *)mvp);

    GameEngine_RendererDraw(&quad->mesh.vao, &quad->mesh.ibo, &quad->shader);
}

GE_Camera_t GameEngine_GFX_CameraOrthoCreate(int width, int height) {
    GE_Camera_t camera = {0};

    glm_mat4_identity(camera.view);
    glm_mat4_identity(camera.projection);

    glm_ortho(0.f, width, 0.f, height, -10.f, 50.f, camera.projection);

    return camera;
}

void GameEngine_GFX_CameraOrthoSetSize(GE_Camera_t *camera, int width, int height) {
    if (camera) {
        glm_ortho(0.f, width, 0.f, height, -10.f, 50.f, camera->projection);
    }
}
