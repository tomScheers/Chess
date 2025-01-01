#include <game_engine/renderer/texture.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>

#include <stdlib.h>

GE_Texture_t GameEngine_TextureCreate(const char *file_path) {
    GE_Texture_t texture;
    texture.file_path = (char *)file_path;
    texture.buffer = NULL;
    texture.id = texture.width = texture.height = texture.bpp = 0;
    
    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    stbi_set_flip_vertically_on_load(1);
    texture.buffer = stbi_load(file_path, &texture.width, &texture.height, &texture.bpp, 4);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.buffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    // If not needed on the CPU
    if(texture.buffer) {
        stbi_image_free(texture.buffer);
    }

    return texture;
}

void GameEngine_TextureDestroy(GE_Texture_t *texture) {
    glDeleteTextures(1, &texture->id);
}

void GameEngine_TextureBind(const GE_Texture_t *texture, unsigned int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture->id);
}

void GameEngine_TextureUnbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}