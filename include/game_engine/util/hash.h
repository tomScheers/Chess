#pragma once

typedef struct GameEngine_HashMapEntry_t {
    char *key;
    int value;
    struct GameEngine_HashMapEntry_t *next;
} GameEngine_HashMapEntry_t;

typedef struct GameEngine_HashMap_t {
    GameEngine_HashMapEntry_t **table;
} GameEngine_HashMap_t;

GameEngine_HashMap_t* GameEngine_HashMapAlloc();
void GameEngine_HashMapFree(GameEngine_HashMap_t *map);

int GameEngine_HashMapFind(GameEngine_HashMap_t *map, const char *key);
void GameEngine_HashMapInsert(GameEngine_HashMap_t *map, const char *key, int value);
void GameEngine_HashMapDeleteEntry(GameEngine_HashMap_t *map, const char *key);

void GameEngine_HashMapPrint(GameEngine_HashMap_t *map);