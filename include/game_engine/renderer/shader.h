#pragma once

typedef struct {
    unsigned int id; 
} GE_Shader_t;

GE_Shader_t GameEngine_ShaderCreate(const char *vs_file_path, const char *fs_file_path);
void GameEngine_ShaderDestroy(GE_Shader_t *shader);

void GameEngine_ShaderBind(const GE_Shader_t *shader);

int GameEngine_ShaderGetUniformLocation(GE_Shader_t *shader, const char *name);

void GameEngine_ShaderSetUniformFloat(GE_Shader_t *shader, const char *name, float value);
void GameEngine_ShaderSetUniformInt(GE_Shader_t *shader, const char *name, int value);
void GameEngine_ShaderSetUniformMat4(GE_Shader_t *shader, const char *name, const float *matrix);