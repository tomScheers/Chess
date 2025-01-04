#pragma once

#include "game_engine/gfx.h"
#include <game_engine/components.h>

#include <engine/engine.h>

// TWEEN

typedef enum {
    TWEEN_STATE_IDLE,
    TWEEN_STATE_RUNNING,
    TWEEN_STATE_PAUSED,
    TWEEN_STATE_COMPLETED
} TweenState;

typedef enum {
    EASE_LINEAR,
    EASE_IN,
    EASE_OUT,
    EASE_IN_OUT
} EasingType;

typedef enum {
    TRANSITION_POSITION,
    TRANSITION_SCALE,
    TRANSITION_ROTATION,
    TRANSITION_ALPHA
} TransitionType;

typedef struct Object_Tween_t {
    float* value;
    float start_value;
    float end_value;
    float duration;
    float current_time;
    TweenState state;
    EasingType easing;
    TransitionType transition;
    void (*on_complete)(void* data); // Optional callback
} Object_Tween_t;

typedef struct Object_TweenManager_t {
    Object_Tween_t** tweens;  // Array of tweens
    size_t count;             // Current number of tweens
    size_t capacity;          // Capacity of the array
} Object_TweenManager_t;

Object_Tween_t* Object_Tween_Create(float* value, float start_value, float end_value, float duration, EasingType easing, TransitionType transition);
void Object_Tween_Destroy(Object_Tween_t* tween);
Object_TweenManager_t* Object_TweenManager_Create();
void Object_TweenManager_Destroy(Object_TweenManager_t* manager);
void Object_TweenManager_AddTween(Object_TweenManager_t* manager, Object_Tween_t* tween);
void Object_TweenManager_RemoveTween(Object_TweenManager_t* manager, Object_Tween_t* tween);
void Object_Tween_Update(Object_Tween_t* tween, float delta_time);
void Object_Tween_Start(Object_Tween_t* tween);
void Object_Tween_Pause(Object_Tween_t* tween);
void Object_Tween_Resume(Object_Tween_t* tween);
void Object_Tween_Stop(Object_Tween_t* tween);
void Object_Tween_SetOnComplete(Object_Tween_t* tween, void (*callback)(void* data));


// CURSOR

typedef struct Object_Cursor_t {
    Object_Tween_t *hold_position_tween;
    CE_Coord hold;
    bool ui, holding;
} Object_Cursor_t;


// BOARD

typedef struct Object_Board_t {
    GE_TexturedQuad_t *quad;
    GE_Transform_t transform;
} Object_Board_t;

Object_Board_t Object_Board_Create();

// PIECE

typedef struct Object_Piece_t {
    GE_TexturedQuad_t *quad;
    GE_Transform_t transform;
    bool held, hovering;
    float yaw, pitch;
} Object_Piece_t;

typedef struct Object_PieceSet_t {
    Object_Piece_t pieces[8][8];
    CE_Game *game;
} Object_PieceSet_t;

Object_PieceSet_t Object_PieceSet_Create(Object_Board_t *board);
void Object_PieceSet_Destroy(Object_PieceSet_t *object);
void Object_PieceSet_Update(Object_PieceSet_t *object, Object_Board_t *board, Object_Cursor_t *cursor, double dt);
void Object_PieceSet_Render(Object_PieceSet_t *object, Object_Cursor_t *cursor, GE_Camera_t *camera);
