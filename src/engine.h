#include <stdlib.h>
#include <stdbool.h>

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

typedef enum Player
{
	WHITE,
	BLACK,
	NONE,
} Player;

typedef struct Coord {
	int y;
	int x;
} Coord;

SquareTypes** createBoard();
void printBoard(SquareTypes **board);
Coord **getValidMoves(SquareTypes **board, Coord *pieceToMove, size_t *returnSize);
void movePiece(SquareTypes **board, Coord *src, Coord *dst);
bool isCheck(SquareTypes **board, Player player);
Player getPlayer(SquareTypes *square);
bool isInRange(int x, int y);
