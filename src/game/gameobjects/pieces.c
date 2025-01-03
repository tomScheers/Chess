#include <game/gameobjects.h>

#include <game_engine/gfx.h>

#include <game/cache.h>

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
				object.pieces[i][j].transform.scale[0] = SQUARE_SIZE;
				object.pieces[i][j].transform.scale[1] = SQUARE_SIZE;
                switch(game->board[i][j]) {
                    case CE_BLACK_PAWN:
                    case CE_WHITE_PAWN:
                    default:
						// Not handled
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

void Object_PieceSet_Render(Object_PieceSet_t *object, GE_Camera_t *camera) {
    for (int row = 0; row < BOARD_SIZE; ++row) {
		for (int col = 0; col < BOARD_SIZE; ++col) {
			// Render
		}
	}
}