#include <game_engine/app.h>
#include <game/gameobjects.h>

#include <game_engine/gfx.h>

#include <game/cache.h>

#include <game_engine/util/math.h>

const int BOARD_SIZE = 8;

Object_PieceSet_t Object_PieceSet_Create(CE_Game *game, Object_Board_t *board) {
    Object_PieceSet_t object;

    int SQUARE_SIZE = board->transform.scale[0]/8;

    object.pieces = (Object_Piece_t **)malloc(BOARD_SIZE * sizeof(Object_Piece_t));

	for (int i = 0; i < BOARD_SIZE; ++i) {
		object.pieces[i] = (Object_Piece_t*)malloc(BOARD_SIZE * sizeof(Object_Piece_t));
		for (int j = 0; j < BOARD_SIZE; ++j) {
            GameEngine_TransformInit(&object.pieces[i][j].transform);
			if (game->board[i][j] != CE_EMPTY) {
				vec2 position = { j * SQUARE_SIZE, i * SQUARE_SIZE };
				object.pieces[i][j].transform.translation[0] = position[0] + board->transform.translation[0];
				object.pieces[i][j].transform.translation[1] = position[1] + board->transform.translation[1];
				object.pieces[i][j].transform.translation[2] = .2f;
				object.pieces[i][j].transform.rotation_origin[0] = object.pieces[i][j].transform.translation[0] + object.pieces[i][j].transform.scale[0]/2;
				object.pieces[i][j].transform.rotation_origin[1] = object.pieces[i][j].transform.translation[1] + object.pieces[i][j].transform.scale[1]/2;
				object.pieces[i][j].transform.scale[0] = SQUARE_SIZE;
				object.pieces[i][j].transform.scale[1] = SQUARE_SIZE;
				object.pieces[i][j].quad = GameEngine_GFX_TexturedQuadCreate();
                switch(game->board[i][j]) {
                    case CE_BLACK_PAWN:
						object.pieces[i][j].quad.texture = Game_g_cache.bpawn_texture;
						break;
                    case CE_BLACK_ROOK:
						object.pieces[i][j].quad.texture = Game_g_cache.brook_texture;
						break;
                    case CE_BLACK_KNIGHT:
						object.pieces[i][j].quad.texture = Game_g_cache.bknight_texture;
						break;
                    case CE_BLACK_BISHOP:
						object.pieces[i][j].quad.texture = Game_g_cache.bbish_texture;
						break;
                    case CE_BLACK_KING:
						object.pieces[i][j].quad.texture = Game_g_cache.bking_texture;
						break;
                    case CE_BLACK_QUEEN:
						object.pieces[i][j].quad.texture = Game_g_cache.bqueen_texture;
						break;
                    case CE_WHITE_PAWN:
						object.pieces[i][j].quad.texture = Game_g_cache.wpawn_texture;
						break;
                    case CE_WHITE_ROOK:
						object.pieces[i][j].quad.texture = Game_g_cache.wrook_texture;
						break;
                    case CE_WHITE_KNIGHT:
						object.pieces[i][j].quad.texture = Game_g_cache.wknight_texture;
						break;
                    case CE_WHITE_BISHOP:
						object.pieces[i][j].quad.texture = Game_g_cache.wbish_texture;
						break;
                    case CE_WHITE_KING:
						object.pieces[i][j].quad.texture = Game_g_cache.wking_texture;
						break;
                    case CE_WHITE_QUEEN:
						object.pieces[i][j].quad.texture = Game_g_cache.wqueen_texture;
						break;
                    default:
						object.pieces[i][j].quad.texture = Game_g_cache.wpawn_texture;
						// object.pieces[i][j].quad.texture = Game_g_cache.debug_texture;
                        break;
                }
			}
		}
	}

    return object;
}

void Object_PieceSet_Destroy(CE_Game *game, Object_PieceSet_t *object) {
    free(object->pieces);
    CE_freeGame(game);
}

void Object_PieceSet_Update(Object_PieceSet_t *object) {
}

void Object_PieceSet_Render(Object_PieceSet_t *object, GE_Camera_t *camera) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            GameEngine_ShaderBind(&object->pieces[i][j].quad.shader);
            GameEngine_TextureBind(&object->pieces[i][j].quad.texture, 0);
            GameEngine_GFX_TexturedQuadRender(&object->pieces[i][j].quad, camera, &object->pieces[i][j].transform);
        }
    }
}
