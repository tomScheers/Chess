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
  src->y = 0;
  src->x = 0;
  dst->y = 0;
  dst->x = 0;
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
      {BLACK_ROOK, BLACK_KNIGHT, BLACK_BISHOP, BLACK_QUEEN, EMPTY, BLACK_BISHOP,
       BLACK_KNIGHT, BLACK_ROOK},
  };
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
  // General tests
  SquareTypes **board1 = createBoard();
  Coord *src = (Coord *)malloc(sizeof(Coord));
  Coord *dst = (Coord *)malloc(sizeof(Coord));

  // Move white king to the centre
  src->x = 4;
  src->y = 0;
  dst->x = 4;
  dst->y = 4;
  movePiece(board1, src, dst);

  // Check all knight checks
  src->x = 6;
  src->y = 7;
  dst->x = 2;
  dst->y = 5;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 2;
  dst->y = 3;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 3;
  dst->y = 6;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 3;
  dst->y = 2;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 5;
  dst->y = 2;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 5;
  dst->y = 6;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 6;
  dst->y = 5;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 6;
  dst->y = 3;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  // Knight check cleanup
  src->x = dst->x;
  src->y = dst->y;
  dst->x = 6;
  dst->y = 7;
  movePiece(board1, src, dst);

  // Pawn Checks
  src->x = 0;
  src->y = 6;
  dst->x = 3;
  dst->y = 5;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 5;
  dst->y = 5;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 3;
  dst->y = 3;
  movePiece(board1, src, dst);

  assert(!isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 5;
  dst->y = 3;
  movePiece(board1, src, dst);

  assert(!isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 0;
  dst->y = 6;
  movePiece(board1, src, dst);

  src->x = 0;
  src->y = 1;
  dst->x = 3;
  dst->y = 5;
  movePiece(board1, src, dst);

  assert(!isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 5;
  dst->y = 5;
  movePiece(board1, src, dst);

  assert(!isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 7;
  dst->y = 7;
  movePiece(board1, src, dst);

  assert(!isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 5;
  dst->y = 7;
  movePiece(board1, src, dst);

  assert(!isCheck(board1, WHITE));

  // Pawn Cleanup
  src->x = dst->x;
  src->y = dst->y;
  dst->x = 0;
  dst->y = 6;
  movePiece(board1, src, dst);

  // Piece used to test if blocking a check with a piece works
  Coord *blockPieceSrc = (Coord *)malloc(sizeof(Coord));
  Coord *blockPieceDst = (Coord *)malloc(sizeof(Coord));

  // Bishop Checks
  src->x = 2;
  src->y = 7;
  dst->x = 1;
  dst->y = 1;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  blockPieceSrc->x = 2;
  blockPieceSrc->y = 1;
  blockPieceDst->x = 2;
  blockPieceDst->y = 2;
  movePiece(board1, blockPieceSrc, blockPieceDst);

  assert(!isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 6;
  dst->y = 6;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 5;
  blockPieceDst->y = 5;
  movePiece(board1, blockPieceSrc, blockPieceDst);

  assert(!isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 2;
  dst->y = 6;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 3;
  blockPieceDst->y = 5;
  movePiece(board1, blockPieceSrc, blockPieceDst);

  assert(!isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 7;
  dst->y = 1;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 6;
  blockPieceDst->y = 2;
  movePiece(board1, blockPieceSrc, blockPieceDst);

  assert(!isCheck(board1, WHITE));

  // Cleanup
  src->x = dst->x;
  src->y = dst->y;
  dst->x = 0;
  dst->y = 0;
  movePiece(board1, src, dst);

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 1;
  blockPieceDst->y = 0;
  movePiece(board1, blockPieceSrc, blockPieceDst);

  // Rook Checks
  src->x = 0;
  src->y = 7;
  dst->x = 0;
  dst->y = 4;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 1;
  blockPieceDst->y = 4;
  movePiece(board1, blockPieceSrc, blockPieceDst);

  assert(!isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 7;
  dst->y = 4;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 6;
  blockPieceDst->y = 4;
  movePiece(board1, blockPieceSrc, blockPieceDst);

  assert(!isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 4;
  dst->y = 6;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 4;
  blockPieceDst->y = 5;
  movePiece(board1, blockPieceSrc, blockPieceDst);

  assert(!isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 4;
  dst->y = 1;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 4;
  blockPieceDst->y = 2;
  movePiece(board1, blockPieceSrc, blockPieceDst);

  assert(!isCheck(board1, WHITE));

  // Clean Up
  src->x = dst->x;
  src->y = dst->y;
  dst->x = 0;
  dst->y = 0;
  movePiece(board1, src, dst);

  // Queen check
  // Diagonal checks
  src->x = 3;
  src->y = 7;
  dst->x = 1;
  dst->y = 1;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 2;
  blockPieceDst->y = 2;
  movePiece(board1, blockPieceSrc, blockPieceDst);

  assert(!isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 6;
  dst->y = 6;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 5;
  blockPieceDst->y = 5;
  movePiece(board1, blockPieceSrc, blockPieceDst);

  assert(!isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 2;
  dst->y = 6;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 3;
  blockPieceDst->y = 5;
  movePiece(board1, blockPieceSrc, blockPieceDst);

  assert(!isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 7;
  dst->y = 1;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 6;
  blockPieceDst->y = 2;
  movePiece(board1, blockPieceSrc, blockPieceDst);
  assert(!isCheck(board1, WHITE));

  // Straight check
  src->x = dst->x;
  src->y = dst->y;
  dst->x = 0;
  dst->y = 4;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 1;
  blockPieceDst->y = 4;
  movePiece(board1, blockPieceSrc, blockPieceDst);

  assert(!isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 7;
  dst->y = 4;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 6;
  blockPieceDst->y = 4;
  movePiece(board1, blockPieceSrc, blockPieceDst);

  assert(!isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 4;
  dst->y = 6;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 4;
  blockPieceDst->y = 5;
  movePiece(board1, blockPieceSrc, blockPieceDst);

  assert(!isCheck(board1, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 4;
  dst->y = 1;
  movePiece(board1, src, dst);

  assert(isCheck(board1, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 4;
  blockPieceDst->y = 2;
  movePiece(board1, blockPieceSrc, blockPieceDst);
  assert(!isCheck(board1, WHITE));
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
