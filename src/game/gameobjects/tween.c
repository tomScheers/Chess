#include <game/gameobjects.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

static float Object_Tween_Ease(EasingType easing, float t) {
    switch (easing) {
        case EASE_LINEAR: return t;
        case EASE_IN: return t * t;
        case EASE_OUT: return 1.0f - (1.0f - t) * (1.0f - t);
        case EASE_IN_OUT:
            if (t < 0.5f) return 2.0f * t * t;
            return 1.0f - pow(-2.0f * t + 2.0f, 2) / 2.0f;
    }
    return t;
}

Object_Tween_t* Object_Tween_Create(float* value, float start_value, float end_value, float duration, EasingType easing, TransitionType transition) {
    Object_Tween_t* tween = (Object_Tween_t*)malloc(sizeof(Object_Tween_t));
    if (!tween) {
        printf("Failed to allocate memory for tween\n");
        return NULL;
    }
    tween->value = value;
    tween->start_value = start_value;
    tween->end_value = end_value;
    tween->duration = duration;
    tween->current_time = 0.0f;
    tween->state = TWEEN_STATE_IDLE;
    tween->easing = easing;
    tween->transition = transition;
    tween->on_complete = NULL; // No default callback

    return tween;
}

void Object_Tween_Destroy(Object_Tween_t* tween) {
    if (tween) {
        free(tween);
    }
}

Object_TweenManager_t* Object_TweenManager_Create() {
    Object_TweenManager_t* manager = (Object_TweenManager_t*)malloc(sizeof(Object_TweenManager_t));
    if (!manager) {
        printf("Failed to allocate memory for tween manager\n");
        return NULL;
    }
    manager->count = 0;
    manager->capacity = 10;  // Starting with room for 10 tweens
    manager->tweens = (Object_Tween_t**)malloc(manager->capacity * sizeof(Object_Tween_t*));
    return manager;
}

void Object_TweenManager_Destroy(Object_TweenManager_t* manager) {
    if (manager) {
        for (size_t i = 0; i < manager->count; i++) {
            Object_Tween_Destroy(manager->tweens[i]);
        }
        free(manager->tweens);
        free(manager);
    }
}

void Object_TweenManager_AddTween(Object_TweenManager_t* manager, Object_Tween_t* tween) {
    if (manager->count == manager->capacity) {
        manager->capacity *= 2;
        manager->tweens = (Object_Tween_t**)realloc(manager->tweens, manager->capacity * sizeof(Object_Tween_t*));
    }
    manager->tweens[manager->count++] = tween;
}

void Object_TweenManager_RemoveTween(Object_TweenManager_t* manager, Object_Tween_t* tween) {
    size_t index = -1;
    for (size_t i = 0; i < manager->count; i++) {
        if (manager->tweens[i] == tween) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        free(manager->tweens[index]);
        for (size_t i = index; i < manager->count - 1; i++) {
            manager->tweens[i] = manager->tweens[i + 1];
        }
        manager->count--;
    }
}

void Object_Tween_Update(Object_Tween_t* tween, float delta_time) {
    if (tween->state == TWEEN_STATE_PAUSED || tween->state == TWEEN_STATE_COMPLETED) return;

    tween->current_time += delta_time;
    if (tween->current_time > tween->duration) {
        tween->current_time = tween->duration;
        tween->state = TWEEN_STATE_COMPLETED;
        if (tween->on_complete) {
            tween->on_complete(tween);
        }
    }

    float progress = tween->current_time / tween->duration;
    float eased_progress = Object_Tween_Ease(tween->easing, progress);

    *tween->value = tween->start_value + eased_progress * (tween->end_value - tween->start_value);
}

void Object_Tween_Start(Object_Tween_t* tween) {
    tween->state = TWEEN_STATE_RUNNING;
    tween->current_time = 0.0f;
}

void Object_Tween_Pause(Object_Tween_t* tween) {
    tween->state = TWEEN_STATE_PAUSED;
}

void Object_Tween_Resume(Object_Tween_t* tween) {
    tween->state = TWEEN_STATE_RUNNING;
}

void Object_Tween_Stop(Object_Tween_t* tween) {
    tween->state = TWEEN_STATE_IDLE;
    *tween->value = tween->start_value; // Reset the value to its start value
}

void Object_Tween_SetOnComplete(Object_Tween_t* tween, void (*callback)(void* data)) {
    tween->on_complete = callback;
}
