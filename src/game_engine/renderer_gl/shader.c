#include <game_engine/renderer/shader.h>
#include <game_engine/util/file.h>

#include <glad/glad.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned int CompileShader(unsigned int type, const char* source) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
        fprintf(stderr, "Shader compilation failed: %s\n", infoLog);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

int GameEngine_ShaderInit(GE_Shader_t *shader, const char *vs_file_path, const char *fs_file_path) {
    char *vs_source = (char *)GameEngine_ReadFile(vs_file_path);
    char *fs_source = (char *)GameEngine_ReadFile(fs_file_path);

    if (!vs_source || !fs_source) {
        free(vs_source);
        free(fs_source);
        return 0;
    }

    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vs_source);
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fs_source);

    free(vs_source);
    free(fs_source);

    if (!vertexShader || !fragmentShader) {
        return 0;
    }

    shader->id = glCreateProgram();
    glAttachShader(shader->id, vertexShader);
    glAttachShader(shader->id, fragmentShader);
    glLinkProgram(shader->id);

    int success;
    char infoLog[512];
    glGetProgramiv(shader->id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader->id, sizeof(infoLog), NULL, infoLog);
        fprintf(stderr, "Program linking failed: %s\n", infoLog);
        glDeleteProgram(shader->id);
        shader->id = 0;
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return 1;
}

void GameEngine_ShaderDestroy(GE_Shader_t *shader) {
    glDeleteProgram(shader->id);
    shader->id = 0;
}

void GameEngine_ShaderUse(const GE_Shader_t *shader) {
    glUseProgram(shader->id);
}

void GameEngine_ShaderSetUniformFloat(const GE_Shader_t *shader, const char *name, float value) {
    int location = glGetUniformLocation(shader->id, name);
    if (location == -1) {
        fprintf(stderr, "Uniform '%s' not found or not used in shader.\n", name);
    } else {
        glUniform1f(location, value);
    }
}

void GameEngine_ShaderSetUniformInt(const GE_Shader_t *shader, const char *name, int value) {
    int location = glGetUniformLocation(shader->id, name);
    if (location == -1) {
        fprintf(stderr, "Uniform '%s' not found or not used in shader.\n", name);
    } else {
        glUniform1i(location, value);
    }
}

void GameEngine_ShaderSetUniformMat4(const GE_Shader_t *shader, const char *name, const float *matrix) {
    int location = glGetUniformLocation(shader->id, name);
    if (location == -1) {
        fprintf(stderr, "Uniform '%s' not found or not used in shader.\n", name);
    } else {
        glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
    }
}