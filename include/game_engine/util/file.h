#include <SDL3/SDL_iostream.h>
#include <stdio.h>
#include <stdlib.h>

const char* GameEngine_ReadFile(const char *file_path) {
    SDL_IOStream* file = SDL_IOFromFile(file_path, "r");
    if(!file) {
        fprintf(stderr, "Failed to open file: %s\n", SDL_GetError());
        return NULL;
    }

    Sint64 file_size = SDL_GetIOSize(file);
    if(file_size <= 0) {
        fprintf(stderr, "Failed to get file size: %s\n", SDL_GetError());
        SDL_CloseIO(file);
        return NULL;
    }

    char* buffer = (char*)malloc(file_size + 1);
    if(!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        SDL_CloseIO(file);
        return NULL;
    }

    Sint64 bytes_read = SDL_ReadIO(file, buffer, file_size);
    if(bytes_read != file_size) {
        fprintf(stderr, "Failed to read the file\n");
        free(buffer);
        SDL_CloseIO(file);
        return NULL;
    }

    buffer[file_size] = '\0';

    SDL_CloseIO(file);

    return buffer;
}

