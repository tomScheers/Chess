#include "../../src/engine.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void testCreateBoard() {
  SquareTypes expectedOutput[8][8] = {
      {WHITE_ROOK, WHITE_KNIGHT, WHITE_BISHOP, WHITE_QUEEN, WHITE_KING,
       WHITE_BISHOP, WHITE_KNIGHT, WHITE_ROOK},
      {WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN,
       WHITE_PAWN, WHITE_PAWN},
      {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
      {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
      {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
      {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
      {BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN,
       BLACK_PAWN, BLACK_PAWN},
      {BLACK_ROOK, BLACK_KNIGHT, BLACK_BISHOP, BLACK_QUEEN, BLACK_KING,
       BLACK_BISHOP, BLACK_KNIGHT, BLACK_ROOK},
  };
  SquareTypes **givenOutput = createBoard();
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      assert(expectedOutput[i][j] == givenOutput[i][j]);
    }
    free(givenOutput[i]);
  }
  free(givenOutput);
}

void testMovePiece() {
  SquareTypes **board = createBoard();
  Coord *src = (Coord *)malloc(sizeof(Coord));
  Coord *dst = (Coord *)malloc(sizeof(Coord));
  src->y = 1;
  src->x = 0;
  dst->y = 2;
  dst->x = 4;
  movePiece(board, src, dst);
  src->y = 7;
  src->x = 4;
  dst->x = 0;
  dst->y = 0;
  movePiece(board, src, dst);
  src->y = 6;
  src->x = 7;
  dst->y = 5;
  dst->x = 4;
  movePiece(board, src, dst);
  SquareTypes expectedBoard[8][8] = {
    {BLACK_KING, WHITE_KNIGHT, WHITE_BISHOP, WHITE_QUEEN, WHITE_KING,
     WHITE_BISHOP, WHITE_KNIGHT, WHITE_ROOK},
    {EMPTY, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN,
     WHITE_PAWN, WHITE_PAWN},
    {EMPTY, EMPTY, EMPTY, EMPTY, WHITE_PAWN, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, BLACK_PAWN, EMPTY, EMPTY, EMPTY},
    {BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN,
     BLACK_PAWN, EMPTY},
    {BLACK_ROOK, BLACK_KNIGHT, BLACK_BISHOP, BLACK_QUEEN, EMPTY,
     BLACK_BISHOP, BLACK_KNIGHT, BLACK_ROOK},
  };
  printBoard(board);
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      assert(board[i][j] == expectedBoard[i][j]);
    }
    free(board[i]);
  }
  free(board);
  free(src);
  free(dst);
}

void testIsCheck() {
  SquareTypes** board1 = createBoard();
  Coord* src = (Coord*)malloc(sizeof(Coord));
  Coord* dst = (Coord*)malloc(sizeof(Coord));
  src->x = 3;
  src->y = 0;
  dst->x = 4;
  dst->y = 6;
  movePiece(board1, src, dst);
  printBoard(board1);
  assert(isCheck(board1, BLACK) == true);
  assert(isCheck(board1, WHITE) == false);
}

int main() {
  testCreateBoard();
  printf("Create Board test passed!\n");
  testMovePiece();
  printf("Move Piece test passed!\n");
  testIsCheck();
  printf("Is Check test passed!\n");
  return EXIT_SUCCESS;
}
