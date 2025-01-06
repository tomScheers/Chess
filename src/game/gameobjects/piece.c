#include <game/gameobjects.h>

#include <game/cache.h>

#include <game_engine/util/math.h>
#include <game_engine/app.h>

#include <string.h>

#include <game_engine/util/audio.h>

void MatchPiecesToGameBoard(Object_PieceSet_t *object, Object_Board_t *board) {
    const int SQUARE_SIZE = board->transform.scale[0] / 8;

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            object->pieces[i][j].quad = NULL;
            object->pieces[i][j].held = false;
            object->pieces[i][j].hovering = false;
            object->pieces[i][j].yaw = 0.f;
            object->pieces[i][j].pitch = 0.f;

            GameEngine_TransformInit(&object->pieces[i][j].transform);
            object->pieces[i][j].transform.scale[0] = (float)SQUARE_SIZE;
            object->pieces[i][j].transform.scale[1] = object->pieces[i][j].transform.scale[0];

            object->pieces[i][j].transform.translation[0] = board->transform.translation[0] + (j * SQUARE_SIZE);
            object->pieces[i][j].transform.translation[1] = board->transform.translation[1] + (i * SQUARE_SIZE);
            object->pieces[i][j].transform.translation[2] = 0.2f;

            object->pieces[i][j].type = object->game->board[i][j];

            if(object->game->board[i][j] != CE_EMPTY) {
                switch(object->game->board[i][j]) {
                    case CE_WHITE_PAWN:
                        object->pieces[i][j].quad = &Game_g_cache.wpawn_quad;
                        break;
                    case CE_BLACK_PAWN:
                        object->pieces[i][j].quad = &Game_g_cache.bpawn_quad;
                        break;
                    case CE_WHITE_ROOK:
                        object->pieces[i][j].quad = &Game_g_cache.wrook_quad;
                        break;
                    case CE_BLACK_ROOK:
                        object->pieces[i][j].quad = &Game_g_cache.brook_quad;
                        break;
                    case CE_WHITE_KNIGHT:
                        object->pieces[i][j].quad = &Game_g_cache.wknight_quad;
                        break;
                    case CE_BLACK_KNIGHT:
                        object->pieces[i][j].quad = &Game_g_cache.bknight_quad;
                        break;
                    case CE_WHITE_BISHOP:
                        object->pieces[i][j].quad = &Game_g_cache.wbish_quad;
                        break;
                    case CE_BLACK_BISHOP:
                        object->pieces[i][j].quad = &Game_g_cache.bbish_quad;
                        break;
                    case CE_WHITE_QUEEN:
                        object->pieces[i][j].quad = &Game_g_cache.wqueen_quad;
                        break;
                    case CE_BLACK_QUEEN:
                        object->pieces[i][j].quad = &Game_g_cache.bqueen_quad;
                        break;
                    case CE_WHITE_KING:
                        object->pieces[i][j].quad = &Game_g_cache.wking_quad;
                        break;
                    case CE_BLACK_KING:
                        object->pieces[i][j].quad = &Game_g_cache.bking_quad;
                        break;
                    default:
                        object->pieces[i][j].quad = &Game_g_cache.debug_quad;
                        break;
                }
            }
        }
    }
}

Object_PieceSet_t Object_PieceSet_Create(Object_Board_t *board) {
    Object_PieceSet_t object;

    object.game = CE_initGame();

    MatchPiecesToGameBoard(&object, board);

    return object;
}

void Object_PieceSet_Destroy(Object_PieceSet_t *object) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            object->pieces[i][j].quad = NULL;
            object->pieces[i][j].held = false;
            object->pieces[i][j].hovering = false;
            object->pieces[i][j].yaw = 0.f;
            object->pieces[i][j].pitch = 0.f;
        }
    }
    
    CE_freeGame(object->game);
}

bool GameEngine_HoveringOnPiece(Object_Piece_t *object, int x, int y) {
	vec2 min = {object->transform.translation[0], object->transform.translation[1]};
	vec2 max = {object->transform.translation[0] + object->transform.scale[0], object->transform.translation[1] + object->transform.scale[1]};
	vec2 point = {x, y};
	if (point[0] >= min[0] && point[0] <= max[0] &&
        point[1] >= min[1] && point[1] <= max[1]) {
		return true;
	}
	return false;
}

void Object_PieceSet_Update(Object_PieceSet_t *object, Object_Board_t *board, Object_Cursor_t *cursor, double dt) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
			vec2 mouse_normalized = {GameEngine_NormalizePosition(GE_g_input_state.mouse_x, GE_g_app.display_width, 1600), 900-GameEngine_NormalizePosition(GE_g_input_state.mouse_y, GE_g_app.display_height, 900)};

            if(GameEngine_HoveringOnPiece(&object->pieces[i][j], mouse_normalized[0], mouse_normalized[1])) {
                object->pieces[i][j].hovering = true;
                if (GE_g_input_state.mouse_buttons[1]) {
                    if (!cursor->holding) {
                        cursor->holding = true;
                        memcpy(&cursor->hold, &(CE_Coord){j, i}, sizeof(CE_Coord));
                        object->pieces[i][j].held = true;
                        if(object->pieces[i][j].type != CE_EMPTY) {
                            GameEngine_AudioPlaySound("data/audio/click.wav");
                        }
                    }
                } else {
                    cursor->holding = false;
                    object->pieces[i][j].held = false;
                    if(cursor->last_state == true && !cursor->holding) {
                        CE_Coord src = cursor->hold;
                        CE_Coord dst = (CE_Coord){j, i};
                        CE_makeValidMove(object->game, &src, &(CE_Coord){j, i});
                        if(object->pieces[cursor->hold.y][cursor->hold.x].type != CE_EMPTY) {
                            GameEngine_AudioPlaySound("data/audio/click.wav");
                        }
                    }
                    MatchPiecesToGameBoard(object, board);
                }

            } else {
                object->pieces[i][j].hovering = false;
            }

			if(object->pieces[i][j].held) {
				object->pieces[i][j].transform.translation[2] = .8f;
				object->pieces[i][j].transform.translation[0] = mouse_normalized[0] - object->pieces[i][j].transform.scale[0]/2;
				object->pieces[i][j].transform.translation[1] = mouse_normalized[1] - object->pieces[i][j].transform.scale[1]/2;
            } else {
				object->pieces[i][j].transform.translation[2] = .2f;
            }
        }
	}

    cursor->last_state = cursor->holding;
}

static CE_Coord **valid_moves = NULL;
static size_t valid_moves_size = 0;
static GE_Transform_t *valid_moves_transforms = NULL;

static void FreeValidMoves() {
    if (valid_moves) {
        for (size_t k = 0; k < valid_moves_size; k++) {
            free(valid_moves[k]);
        }
        free(valid_moves);
        valid_moves = NULL;
        valid_moves_size = 0;
    }
    if (valid_moves_transforms) {
        free(valid_moves_transforms);
        valid_moves_transforms = NULL;
    }
}

void Object_PieceSet_Render(Object_PieceSet_t *object, Object_Cursor_t *cursor, GE_Camera_t *camera) {
    if (cursor->holding) {
        FreeValidMoves();
        valid_moves = CE_getValidMoves(object->game, &cursor->hold, &valid_moves_size);

        if (valid_moves && valid_moves_size > 0) {
            valid_moves_transforms = (GE_Transform_t *)malloc(valid_moves_size * sizeof(GE_Transform_t));
            if (!valid_moves_transforms) {
                FreeValidMoves();
                return;
            }

            for (size_t k = 0; k < valid_moves_size; k++) {
                if (valid_moves[k]) {
                    valid_moves_transforms[k] = object->pieces[valid_moves[k]->y][valid_moves[k]->x].transform;
                    valid_moves_transforms[k].translation[2] = 0.5f;
                }
            }
        }
    } else {
        FreeValidMoves();
    }

    if (valid_moves && valid_moves_size > 0 && valid_moves_transforms) {
        for (size_t k = 0; k < valid_moves_size; k++) {
            if (valid_moves[k]) {
                GameEngine_ShaderBind(&Game_g_cache.notch_quad.shader);
                GameEngine_TextureBind(&Game_g_cache.notch_quad.texture, 0);
                GameEngine_GFX_TexturedQuadRender(&Game_g_cache.notch_quad, camera, &valid_moves_transforms[k]);
            }
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (object->pieces[i][j].quad != NULL && object->game->board[i][j] != CE_EMPTY) {
                GameEngine_ShaderBind(&object->pieces[i][j].quad->shader);
                GameEngine_TextureBind(&object->pieces[i][j].quad->texture, 0);
                GameEngine_GFX_TexturedQuadRender(object->pieces[i][j].quad, camera, &object->pieces[i][j].transform);
            }
        }
    }
}
