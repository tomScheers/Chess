#ifndef ENGINE_H
#define ENGINE_H

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


typedef enum {
	CE_EMPTY = 0,
	CE_BLACK_BISHOP,
	CE_BLACK_PAWN,
	CE_BLACK_KING,
	CE_BLACK_ROOK,
	CE_BLACK_QUEEN,
	CE_BLACK_KNIGHT,
	CE_WHITE_BISHOP,
	CE_WHITE_PAWN,
	CE_WHITE_KING,
	CE_WHITE_ROOK,
	CE_WHITE_QUEEN,
	CE_WHITE_KNIGHT,
} CE_SquareTypes;

typedef enum Player {
	CE_WHITE_PLAYER,
	CE_BLACK_PLAYER,
	CE_NO_PLAYER,
} CE_Player;

typedef enum {
	CE_STATE_STALEMATE,
	CE_STATE_ONGOING,
} CE_GameState;

typedef struct {
	int x;
	int y;
} CE_Coord;

typedef struct {
	CE_SquareTypes** board;
	bool whiteHasCastleRight[2]; // 2 for both sides
	bool blackHasCastleRight[2]; // 2 for both sides
	CE_Player currPlayer;
	time_t startTime;
	CE_Coord* enPassantSquare;
} CE_Game;

CE_Game* CE_initGame();
CE_Coord** CE_getValidMoves(CE_Game *game, CE_Coord *pieceToMove, size_t *returnSize);
bool CE_makeValidMove(CE_Game *game, CE_Coord *src, CE_Coord *dst);
CE_GameState CE_getGameState(CE_Game *game);

#endif
