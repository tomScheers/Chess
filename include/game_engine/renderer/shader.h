#pragma once

typedef struct {
    unsigned int id; 
} GE_Shader_t;

int GameEngine_ShaderInit(GE_Shader_t *shader, const char *vs_file_path, const char *fs_file_path);
void GameEngine_ShaderDestroy(GE_Shader_t *shader);

void GameEngine_ShaderUse(const GE_Shader_t *shader);

void GameEngine_ShaderSetUniformFloat(const GE_Shader_t *shader, const char *name, float value);
void GameEngine_ShaderSetUniformInt(const GE_Shader_t *shader, const char *name, int value);
void GameEngine_ShaderSetUniformMat4(const GE_Shader_t *shader, const char *name, const float *matrix);