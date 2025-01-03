#pragma once

static float GameEngine_NormalizePosition(float pos, int original_size, int target_size) {
    return (float)(pos / original_size) * target_size;
}