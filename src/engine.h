#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef enum SquareTypes
{
	EMPTY = 0,
	BLACK_BISHOP,
	BLACK_PAWN,
	BLACK_KING,
	BLACK_ROOK,
	BLACK_QUEEN,
	BLACK_KNIGHT,
	WHITE_BISHOP,
	WHITE_PAWN,
	WHITE_KING,
	WHITE_ROOK,
	WHITE_QUEEN,
	WHITE_KNIGHT,
} SquareTypes;

typedef enum Player {
	WHITE,
	BLACK,
	NONE,
} Player;

typedef struct Coord {
	int x;
	int y;
} Coord;

typedef struct Game {
	SquareTypes** board;
	bool whiteHasCastleRight;
	bool blackHasCastleRight;
	Player currPlayer;
	time_t startTime;
	Coord* enPassantSquare;
} Game;

SquareTypes** createBoard();
void printBoard(Game *game);
Coord **getValidMoves(Game *game, Coord *pieceToMove, size_t *returnSize);
void movePiece(SquareTypes **game, Coord *src, Coord *dst);
bool isCheck(Game *game, Player player);
bool isCurrPlayerCheck(Game *game);
Game* initGame();
