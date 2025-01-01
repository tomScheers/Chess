#pragma once

typedef struct {
    char *file_path;
    unsigned char *loc_buffer;
    unsigned int id;
    int width, height, bpp;
} GE_Texture_t;

GE_Texture_t GameEngine_TextureCreate(const char *file_path);
void GameEngine_TextureDestroy(GE_Texture_t *texture);

void GameEngine_TextureBind(const GE_Texture_t *texture, unsigned int slot);
void GameEngine_TextureUnbind();