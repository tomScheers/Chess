// This engine is behind on the newest version
// If you want to track the newwest version, see the engine branch
#include "engine.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

SquareTypes** createBoard() {
	SquareTypes** board = (SquareTypes **)malloc(sizeof(SquareTypes*) * 8);
	for (int i = 0; i < 8; ++i) {
		board[i] = (SquareTypes *)malloc(sizeof(SquareTypes) * 8);
	}
	// yeah, I tried to generat
	// Is vscode so buggy for you too
	// It keeps giving me weird errors and it comments my code [the formatter]
	board[0][0] = WHITE_ROOK;
	board[0][1] = WHITE_KNIGHT;
	board[0][2] = WHITE_BISHOP;
	board[0][3] = WHITE_QUEEN;
	board[0][4] = WHITE_KING;
	board[0][5] = WHITE_BISHOP;
	board[0][6] = WHITE_KNIGHT;
	board[0][7] = WHITE_ROOK;
	board[7][0] = BLACK_ROOK;
	board[7][1] = BLACK_KNIGHT;
	board[7][2] = WHITE_BISHOP;
	board[7][3] = WHITE_QUEEN;
	board[7][4] = WHITE_KING;
	board[7][5] = WHITE_BISHOP;
	board[7][6] = WHITE_KNIGHT;
	board[7][7] = WHITE_ROOK;
	for (int i = 0; i < 8; ++i)
	{
		board[1][i] = WHITE_PAWN;
		board[6][i] = BLACK_PAWN;
	}
	for (int i = 2; i < 6; ++i) {
		for (int j = 0; j < 8; ++j) {
			board[i][j] = EMPTY;
		}
	}
	return board;
}

void printBoard(SquareTypes **board) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			switch(board[i][j]) {
				case WHITE_ROOK:
				case BLACK_ROOK:
					printf("Rook ");
					break;
				case WHITE_KNIGHT:
				case BLACK_KNIGHT:
					printf("Knight ");
					break;
				case WHITE_BISHOP:
				case BLACK_BISHOP:
					printf("Bishop ");
					break;
				case WHITE_QUEEN:
				case BLACK_QUEEN:
					printf("Queen ");
					break;
				case WHITE_KING:
				case BLACK_KING:
					printf("King ");
					break;
				case WHITE_PAWN:
				case BLACK_PAWN:
					printf("Pawn ");
					break;
				case EMPTY:
					printf("Empty ");
					break;
				}
		}
		printf("\n");
	}
}

bool isCheck(SquareTypes** board, Player player) {
	SquareTypes *king = player == WHITE ? WHITE_KING : BLACK_KING;
	SquareTypes *oposingRook = player == WHITE ? BLACK_ROOK : WHITE_ROOK;
	SquareTypes *oposingQueen = player == WHITE ? BLACK_QUEEN : WHITE_QUEEN;
	SquareTypes *oposingBishop = player == WHITE ? BLACK_BISHOP : WHITE_BISHOP;
	SquareTypes *oposingPawn = player == WHITE ? BLACK_PAWN : WHITE_PAWN;
	SquareTypes *oposingKnight = player == WHITE ? BLACK_KNIGHT : WHITE_KNIGHT;

	// Black's pawns move 'downwards' from the arrays perspective, so the program needs to take that into acount
	int moveIncrement = player == WHITE ? 1 : -1;

	Coord *kingCoords;
	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x) {
			if (board[y][x] == king) {
				kingCoords = (Coord *){x, y};
				break;
			}
		}
		if (kingCoords != NULL)
			break;
	}

	// Check for horizontal queen and rook checks
	// Check from right-hand side
	for (int y = kingCoords->y; y < 8; ++y) {
		if (board[y][kingCoords->x] == oposingRook || board[y][kingCoords->x] == oposingQueen)
			return true;
		if (board[y][kingCoords->x] != EMPTY)
			break;
	}
	// Check from left-hand side
	for (int y = kingCoords->y; y > 0; --y) {
		if (board[y][kingCoords->x] == oposingRook || board[y][kingCoords->x] == oposingQueen)
			return true;
		if (board[y][kingCoords->x] != EMPTY)
			break;
	}

	// Check for vertical queen and rook checks
	// Check from right-hand side
	for (int x = kingCoords->x; x > 0; ++x) {
		if (board[kingCoords->y][x] == oposingRook || board[kingCoords->y][x] == oposingQueen)
			return true;
		if (board[kingCoords->y][x] != EMPTY)
			break;
	}
	// Check from left-hand side
	for (int x = kingCoords->x; x > 0; --x) {
		if (board[kingCoords->y][x] == oposingRook || board[kingCoords->y][x] == oposingQueen)
			return true;
		if (board[kingCoords->y][x] != EMPTY)
			break;
	}

	// Check pawn checks
	if (board[kingCoords->y + moveIncrement][kingCoords->x + 1] == oposingPawn || board[kingCoords->y + moveIncrement][kingCoords->x + 1] == oposingPawn)
		return true;

	// Check for knight checks
	if (board[kingCoords->y + 2][kingCoords->x + 1] == oposingKnight)
		return true;

	if (board[kingCoords->y + 2][kingCoords->x - 1] == oposingKnight)
		return true;

	if (board[kingCoords->y + 1][kingCoords->x - 2] == oposingKnight)
		return true;

	if (board[kingCoords->y - 1][kingCoords->x - 2] == oposingKnight)
		return true;

	if (board[kingCoords->y - 2][kingCoords->x + 1] == oposingKnight)
		return true;
	
	if (board[kingCoords->y - 2][kingCoords->x - 1] == oposingKnight)
		return true;
	
	if (board[kingCoords->y + 1][kingCoords->x + 2] == oposingKnight)
		return true;
	
	if (board[kingCoords->y - 1][kingCoords->x + 2] == oposingKnight)
		return true;
	

	// Check for bishop and queen diagnol checks
	for (int i = kingCoords->x; i < 8; ++i) {
		if (board[kingCoords->y + i][kingCoords->x + i] == oposingBishop || board[kingCoords->y + i][kingCoords->x + i] == oposingQueen)
			return true;
		if (board[kingCoords->y + i][kingCoords->x + i] != EMPTY)
			break;
	}

	for (int i = kingCoords->x; i < 8; ++i) {
		if (board[kingCoords->y - i][kingCoords->x + i] == oposingBishop || board[kingCoords->y - i][kingCoords->x + i] == oposingQueen)
			return true;
		if (board[kingCoords->y - i][kingCoords->x + i] != EMPTY)
			break;
	}
	
	for (int i = kingCoords->x; i > 0; --i) {
		if (board[kingCoords->y - i][kingCoords->x + i] == oposingBishop || board[kingCoords->y - i][kingCoords->x + i] == oposingQueen)
			return true;
		if (board[kingCoords->y - i][kingCoords->x + i] != EMPTY)
			break;
	}

	for (int i = kingCoords->x; i > 0; --i) {
		if (board[kingCoords->y + i][kingCoords->x + i] == oposingBishop || board[kingCoords->y + i][kingCoords->x + i] == oposingQueen)
			return true;
		if (board[kingCoords->y + i][kingCoords->x + i] != EMPTY)
			break;
	}
}

// TODO: add the rest of the pieces, but before that I need a move and ischeck function to check if the move is valid or if the player is then in check
Coord **getValidMoves(SquareTypes** board, Coord* pieceToMove, size_t returnSize) {
	Coord **validMoves;
	size_t validMovesIndex = 0;
	int yOrigin = pieceToMove->y;
	int xOrigin = pieceToMove->x;
	switch (board[pieceToMove->y][pieceToMove->x])
	{
	case WHITE_PAWN:
		if (board[pieceToMove->y + 1][pieceToMove->x] == EMPTY) {
			validMoves[validMovesIndex++] = (Coord *){yOrigin + 1, xOrigin};
		}
		if (board[pieceToMove->y + 1][pieceToMove->x + 1] != EMPTY) {
			validMoves[validMovesIndex++] = (Coord *){yOrigin + 1, xOrigin + 1};
		}
		if (board[pieceToMove->y + 1][pieceToMove->x - 1] != EMPTY) {
			validMoves[validMovesIndex++] = (Coord *){yOrigin + 1, xOrigin - 1};
		}
	}
	returnSize = validMovesIndex;
}
 int main() {
 	SquareTypes **board = createBoard();
 	printf("Created board\n");
 	printBoard(board);
 	printf("Finished");
	size_t coordSize = 0;
	Coord **validMoves = getValidMoves(board, (Coord *){0, 3}, coordSize);
	for (int i = 0; i < coordSize; ++i) {
		printf("%d, %d\n", validMoves[i]->x, validMoves[i]->y);
	}
	return EXIT_SUCCESS;
 }
