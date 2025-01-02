#include <game_engine/util/hash.h>

#include "SDL3/SDL_stdinc.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_HASH_ENTRY_COUNT 128

unsigned int hash(const char *key) {
    unsigned int hashValue = 0;
    while (*key) {
        hashValue = (hashValue * 31) + *key;
        key++;
    }
    return hashValue % MAX_HASH_ENTRY_COUNT;
}

GameEngine_HashMap_t *GameEngine_HashMapAlloc() {
    GameEngine_HashMap_t *map = (GameEngine_HashMap_t*)malloc(sizeof(GameEngine_HashMap_t));
    map->table = (GameEngine_HashMapEntry_t**)malloc(sizeof(GameEngine_HashMapEntry_t*) * MAX_HASH_ENTRY_COUNT);
    
    for (int i = 0; i < MAX_HASH_ENTRY_COUNT; i++) {
        map->table[i] = NULL;
    }
    
    return map;
}

void GameEngine_HashMapFree(GameEngine_HashMap_t *map) {
    for (int i = 0; i < MAX_HASH_ENTRY_COUNT; i++) {
        GameEngine_HashMapEntry_t *entry = map->table[i];
        while (entry) {
            GameEngine_HashMapEntry_t *next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    free(map->table);
    free(map);
}

int GameEngine_HashMapFind(GameEngine_HashMap_t *map, const char *key) {
    unsigned int index = hash(key);
    GameEngine_HashMapEntry_t *entry = map->table[index];
    
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    
    
    return -1;
}

void GameEngine_HashMapInsert(GameEngine_HashMap_t *map, const char *key, int value) {
    unsigned int index = hash(key);
    
    GameEngine_HashMapEntry_t *new_entry = (GameEngine_HashMapEntry_t *)malloc(sizeof(GameEngine_HashMapEntry_t));
    new_entry->key = SDL_strdup(key);
    new_entry->value = value;
    new_entry->next = map->table[index];
    
    map->table[index] = new_entry;
}

void GameEngine_HashMapDeleteEntry(GameEngine_HashMap_t *map, const char *key) {
    unsigned int index = hash(key);
    GameEngine_HashMapEntry_t *entry = map->table[index];
    GameEngine_HashMapEntry_t *prev = NULL;
    
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            if (prev) {
                prev->next = entry->next;
            } else {
                map->table[index] = entry->next;
            }
            free(entry->key);
            free(entry);
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

void GameEngine_HashMapPrint(GameEngine_HashMap_t *map) {
    for (int i = 0; i < MAX_HASH_ENTRY_COUNT; i++) {
        GameEngine_HashMapEntry_t *entry = map->table[i];
        while (entry) {
            printf("Key: %s, Value: %d\n", entry->key, entry->value);
            entry = entry->next;
        }
    }
}