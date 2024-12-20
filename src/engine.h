#include <stdlib.h>
#include <stdbool.h>
// I'm having too many issues with live share, I'm not sure I can continue like this, might have to switch to more traditional pull request system
// Yea that might be better, I do have to do a little research then but that will be fine
// Then I can also use nvim

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
} Player;

typedef struct Coord {
	int y;
	int x;
} Coord;

SquareTypes** createBoard();
void printBoard(SquareTypes **board);
Coord **getValidMoves(SquareTypes **board, Coord pieceToMove, size_t returnSize);