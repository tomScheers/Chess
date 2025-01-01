#include <game_engine/renderer/texture.h>

#include <glad/glad.h>

#include <stdlib.h>

GE_Texture_t GameEngine_TextureCreate(const char *file_path) {
    GE_Texture_t texture;
    texture.file_path = (char *)file_path;
    texture.loc_buffer = NULL;
    texture.id = texture.width = texture.height = texture.bpp = 0;
    
    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    return texture;
}

void GameEngine_TextureDestroy(GE_Texture_t *texture) {

}

void GameEngine_TextureBind(const GE_Texture_t *texture, unsigned int slot) {

}

void GameEngine_TextureUnbind() {

}