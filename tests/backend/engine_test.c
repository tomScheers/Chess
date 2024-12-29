#include "../../src/engine_internal.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void testCreateBoard() {
  CE_SquareTypes expectedOutput[8][8] = {
      {CE_WHITE_ROOK, CE_WHITE_KNIGHT, CE_WHITE_BISHOP, CE_WHITE_QUEEN,
       CE_WHITE_KING, CE_WHITE_BISHOP, CE_WHITE_KNIGHT, CE_WHITE_ROOK},
      {CE_WHITE_PAWN, CE_WHITE_PAWN, CE_WHITE_PAWN, CE_WHITE_PAWN,
       CE_WHITE_PAWN, CE_WHITE_PAWN, CE_WHITE_PAWN, CE_WHITE_PAWN},
      {CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY,
       CE_EMPTY},
      {CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY,
       CE_EMPTY},
      {CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY,
       CE_EMPTY},
      {CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY,
       CE_EMPTY},
      {CE_BLACK_PAWN, CE_BLACK_PAWN, CE_BLACK_PAWN, CE_BLACK_PAWN,
       CE_BLACK_PAWN, CE_BLACK_PAWN, CE_BLACK_PAWN, CE_BLACK_PAWN},
      {CE_BLACK_ROOK, CE_BLACK_KNIGHT, CE_BLACK_BISHOP, CE_BLACK_QUEEN,
       CE_BLACK_KING, CE_BLACK_BISHOP, CE_BLACK_KNIGHT, CE_BLACK_ROOK},
  };
  CE_SquareTypes **givenOutput = CE__createBoard();
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      assert(expectedOutput[i][j] == givenOutput[i][j]);
    }
    free(givenOutput[i]);
  }
  free(givenOutput);
}

void testMovePiece() {
  CE_Game* game = CE_initGame();
  CE_Coord *src = (CE_Coord *)malloc(sizeof(CE_Coord));
  CE_Coord *dst = (CE_Coord *)malloc(sizeof(CE_Coord));
  src->y = 1;
  src->x = 0;
  dst->y = 2;
  dst->x = 4;
  CE__movePiece(game, src, dst);
  src->y = 7;
  src->x = 4;
  dst->x = 0;
  dst->y = 0; CE__movePiece(game, src, dst);
  src->y = 6;
  src->x = 7;
  dst->y = 5;
  dst->x = 4;
  CE__movePiece(game, src, dst);
  src->y = 0;
  src->x = 0;
  dst->y = 0;
  dst->x = 0;
  CE__movePiece(game, src, dst);
  CE_SquareTypes expectedBoard[8][8] = {
      {CE_BLACK_KING, CE_WHITE_KNIGHT, CE_WHITE_BISHOP, CE_WHITE_QUEEN,
       CE_WHITE_KING, CE_WHITE_BISHOP, CE_WHITE_KNIGHT, CE_WHITE_ROOK},
      {CE_EMPTY, CE_WHITE_PAWN, CE_WHITE_PAWN, CE_WHITE_PAWN, CE_WHITE_PAWN,
       CE_WHITE_PAWN, CE_WHITE_PAWN, CE_WHITE_PAWN},
      {CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_WHITE_PAWN, CE_EMPTY,
       CE_EMPTY, CE_EMPTY},
      {CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY,
       CE_EMPTY},
      {CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY,
       CE_EMPTY},
      {CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_EMPTY, CE_BLACK_PAWN, CE_EMPTY,
       CE_EMPTY, CE_EMPTY},
      {CE_BLACK_PAWN, CE_BLACK_PAWN, CE_BLACK_PAWN, CE_BLACK_PAWN,
       CE_BLACK_PAWN, CE_BLACK_PAWN, CE_BLACK_PAWN, CE_EMPTY},
      {CE_BLACK_ROOK, CE_BLACK_KNIGHT, CE_BLACK_BISHOP, CE_BLACK_QUEEN,
       CE_EMPTY, CE_BLACK_BISHOP, CE_BLACK_KNIGHT, CE_BLACK_ROOK},
  };
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      assert(game->board[i][j] == expectedBoard[i][j]);
    }
    free(game->board[i]);
  }
  free(game->board);
  free(src);
  free(dst);
  free(game);
}

void testIsCheck() {
  // General tests
  CE_Game *game = CE_initGame();
  CE_Coord *src = (CE_Coord *)malloc(sizeof(CE_Coord));
  CE_Coord *dst = (CE_Coord *)malloc(sizeof(CE_Coord));

  // Move white king to the centre
  src->x = 4;
  src->y = 0;
  dst->x = 4;
  dst->y = 4;
  CE__movePiece(game, src, dst);

  // Check all knight checks
  src->x = 6;
  src->y = 7;
  dst->x = 2;
  dst->y = 5;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 2;
  dst->y = 3;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 3;
  dst->y = 6;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 3;
  dst->y = 2;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 5;
  dst->y = 2;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 5;
  dst->y = 6;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 6;
  dst->y = 5;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 6;
  dst->y = 3;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  // Knight check cleanup
  src->x = dst->x;
  src->y = dst->y;
  dst->x = 6;
  dst->y = 7;
  CE__movePiece(game, src, dst);

  // Pawn Checks
  src->x = 0;
  src->y = 6;
  dst->x = 3;
  dst->y = 5;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 5;
  dst->y = 5;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 3;
  dst->y = 3;
  CE__movePiece(game, src, dst);

  assert(!CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 5;
  dst->y = 3;
  CE__movePiece(game, src, dst);

  assert(!CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 0;
  dst->y = 6;
  CE__movePiece(game, src, dst);

  src->x = 0;
  src->y = 1;
  dst->x = 3;
  dst->y = 5;
  CE__movePiece(game, src, dst);

  assert(!CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 5;
  dst->y = 5;
  CE__movePiece(game, src, dst);

  assert(!CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 7;
  dst->y = 7;
  CE__movePiece(game, src, dst);

  assert(!CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 5;
  dst->y = 7;
  CE__movePiece(game, src, dst);

  assert(!CE__isCheck(game, CE_WHITE_PLAYER));

  // Pawn Cleanup
  src->x = dst->x;
  src->y = dst->y;
  dst->x = 0;
  dst->y = 6;
  CE__movePiece(game, src, dst);

  // Piece used to test if blocking a check with a piece works
  CE_Coord *blockPieceSrc = (CE_Coord *)malloc(sizeof(CE_Coord));
  CE_Coord *blockPieceDst = (CE_Coord *)malloc(sizeof(CE_Coord));

  // Bishop Checks
  src->x = 2;
  src->y = 7;
  dst->x = 1;
  dst->y = 1;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  blockPieceSrc->x = 2;
  blockPieceSrc->y = 1;
  blockPieceDst->x = 2;
  blockPieceDst->y = 2;
  CE__movePiece(game, blockPieceSrc, blockPieceDst);

  assert(!CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 6;
  dst->y = 6;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 5;
  blockPieceDst->y = 5;
  CE__movePiece(game, blockPieceSrc, blockPieceDst);

  assert(!CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 2;
  dst->y = 6;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 3;
  blockPieceDst->y = 5;
  CE__movePiece(game, blockPieceSrc, blockPieceDst);

  assert(!CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 7;
  dst->y = 1;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 6;
  blockPieceDst->y = 2;
  CE__movePiece(game, blockPieceSrc, blockPieceDst);

  assert(!CE__isCheck(game, CE_WHITE_PLAYER));

  // Cleanup
  src->x = dst->x;
  src->y = dst->y;
  dst->x = 0;
  dst->y = 0;
  CE__movePiece(game, src, dst);

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 1;
  blockPieceDst->y = 0;
  CE__movePiece(game, blockPieceSrc, blockPieceDst);

  // Rook Checks
  src->x = 0;
  src->y = 7;
  dst->x = 0;
  dst->y = 4;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 1;
  blockPieceDst->y = 4;
  CE__movePiece(game, blockPieceSrc, blockPieceDst);

  assert(!CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 7;
  dst->y = 4;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 6;
  blockPieceDst->y = 4;
  CE__movePiece(game, blockPieceSrc, blockPieceDst);

  assert(!CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 4;
  dst->y = 6;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 4;
  blockPieceDst->y = 5;
  CE__movePiece(game, blockPieceSrc, blockPieceDst);

  assert(!CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 4;
  dst->y = 1;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 4;
  blockPieceDst->y = 2;
  CE__movePiece(game, blockPieceSrc, blockPieceDst);

  assert(!CE__isCheck(game, CE_WHITE_PLAYER));

  // Clean Up
  src->x = dst->x;
  src->y = dst->y;
  dst->x = 0;
  dst->y = 0;
  CE__movePiece(game, src, dst);

  // Queen check
  // Diagonal checks
  src->x = 3;
  src->y = 7;
  dst->x = 1;
  dst->y = 1;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 2;
  blockPieceDst->y = 2;
  CE__movePiece(game, blockPieceSrc, blockPieceDst);

  assert(!CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 6;
  dst->y = 6;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 5;
  blockPieceDst->y = 5;
  CE__movePiece(game, blockPieceSrc, blockPieceDst);

  assert(!CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 2;
  dst->y = 6;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 3;
  blockPieceDst->y = 5;
  CE__movePiece(game, blockPieceSrc, blockPieceDst);

  assert(!CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 7;
  dst->y = 1;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 6;
  blockPieceDst->y = 2;
  CE__movePiece(game, blockPieceSrc, blockPieceDst);
  assert(!CE__isCheck(game, CE_WHITE_PLAYER));

  // Straight check
  src->x = dst->x;
  src->y = dst->y;
  dst->x = 0;
  dst->y = 4;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 1;
  blockPieceDst->y = 4;
  CE__movePiece(game, blockPieceSrc, blockPieceDst);

  assert(!CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 7;
  dst->y = 4;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 6;
  blockPieceDst->y = 4;
  CE__movePiece(game, blockPieceSrc, blockPieceDst);

  assert(!CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 4;
  dst->y = 6;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 4;
  blockPieceDst->y = 5;
  CE__movePiece(game, blockPieceSrc, blockPieceDst);

  assert(!CE__isCheck(game, CE_WHITE_PLAYER));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 4;
  dst->y = 1;
  CE__movePiece(game, src, dst);

  assert(CE__isCheck(game, CE_WHITE_PLAYER));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 4;
  blockPieceDst->y = 2;
  CE__movePiece(game, blockPieceSrc, blockPieceDst);
  assert(!CE__isCheck(game, CE_WHITE_PLAYER));
}

void assertValidMoves(CE_Coord **expected, size_t expectedSize, CE_Coord **given,
                      size_t givenSize) {
  printf("expectedSize: %zu, givenSize: %zu\n", expectedSize, givenSize);
  assert(expectedSize == givenSize);
  for (size_t i = 0; i < givenSize; ++i) {
    assert(given[i] != NULL);
    assert(expected[i] != NULL);
  }
  for (size_t i = 0; i < givenSize; ++i) {
    CE_Coord *givenCoord = given[i];
    bool isGiven = false;
    for (size_t j = 0; j < expectedSize; ++j) {
      printf("(%d, %d) == (%d, %d)\n", givenCoord->x, givenCoord->y,
             expected[j]->x, expected[j]->y);
      if (givenCoord->x == expected[j]->x && givenCoord->y == expected[j]->y) {
        isGiven = true;
        break;
      }
    }
    assert(isGiven);
  }
}

void testGetValidMoves() {
  CE_Game *game = CE_initGame();
  printf("Print after creation:\n");
  CE__printBoard(game);
  printf("\n\n\n\n");
  size_t retSize = 0;
  CE_Coord **validMoves = CE_getValidMoves(game, &(CE_Coord){0, 1}, &retSize);
  CE__printBoard(game);
  printf("Valid moves:\n");
  for (size_t i = 0; i < retSize; ++i) {
    printf("(%d, %d)\n", validMoves[i]->x, validMoves[i]->y);
  }
  CE_Coord e1 = {0, 2};
  CE_Coord e2 = {0, 3}; // Long jump
  CE_Coord *expected[] = {
      &e1,
      &e2,
  };
  assertValidMoves(expected, 2, validMoves, retSize);
  printf("Board before moving:\n");
  CE__printBoard(game);
  printf("\n\n");
  CE__movePiece(game, &(CE_Coord){0, 1}, &(CE_Coord){1, 5});
  size_t retSize2 = 0;
  CE_Coord **validMoves2 = CE_getValidMoves(game, &(CE_Coord){1, 5}, &retSize2);
  printf("Valid moves:\n");
  for (size_t i = 0; i < retSize2; ++i) {
    printf("(%d, %d)\n", validMoves2[i]->x, validMoves2[i]->y);
  }

  CE_Coord e3 = {0, 6};
  CE_Coord e4 = {2, 6};
  CE_Coord *expected2[] = {
      &e3,
      &e4,
  };
  assertValidMoves(expected2, 2, validMoves2, retSize2);

  // Test for en passant
  CE__movePiece(game, &(CE_Coord){1, 5}, &(CE_Coord){1, 4});
  CE__movePiece(game, &(CE_Coord){2, 6}, &(CE_Coord){2, 4});
  game->enPassantSquare = &(CE_Coord){2, 5};

  size_t retSize3 = 0;
  CE_Coord **validMoves3 = CE_getValidMoves(game, &(CE_Coord){1, 4}, &retSize3);

  for (size_t i = 0; i < retSize3; ++i) {
    printf("(%d, %d)\n", validMoves3[i]->x, validMoves3[i]->y);
  }
  CE_Coord e5 = {1, 5};
  CE_Coord e6 = {2, 5};
  CE_Coord *expected3[] = {
      &e5,
      &e6,
  };
  assertValidMoves(expected3, 2, validMoves3, retSize3);

  // Reset board
  game->board = CE__createBoard();

  // Rook Tests
  size_t retSize4 = 0;
  CE__movePiece(game, &(CE_Coord){0, 0}, &(CE_Coord){3, 0});
  CE_getValidMoves(game, &(CE_Coord){0, 0}, &retSize4);
  // Assert that there are no valid moves
  assert(retSize4 == 0);

  CE__movePiece(game, &(CE_Coord){3, 0}, &(CE_Coord){4, 4});
  size_t retSize5 = 0;
  CE_Coord **validMoves5 = CE_getValidMoves(game, &(CE_Coord){4, 4}, &retSize5);
  CE_Coord e7 = {3, 4};
  CE_Coord e8 = {2, 4};
  CE_Coord e9 = {1, 4};
  CE_Coord e10 = {0, 4};
  CE_Coord e11 = {5, 4};
  CE_Coord e12 = {6, 4};
  CE_Coord e13 = {7, 4};
  CE_Coord e14 = {4, 3};
  CE_Coord e15 = {4, 2};
  CE_Coord e16 = {4, 5};
  CE_Coord e17 = {4, 6};
  CE_Coord *expected4[] = {
      &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15, &e16, &e17,
  };
  CE__printBoard(game);
  for (size_t i = 0; i < retSize5; ++i) {
    printf("given[i]: (%d, %d)\n", validMoves5[i]->x, validMoves5[i]->y);
  }
  assertValidMoves(expected4, 11, validMoves5, retSize5);

  // Reset board
  game->board = CE__createBoard();

  // Bishop tests
  size_t retSize6 = 0;
  CE_Coord **validMoves6 = CE_getValidMoves(game, &(CE_Coord){2, 0}, &retSize6);
  // Assert that there are no valid moves
  CE__printBoard(game);
  for (size_t i = 0; i < retSize6; ++i) {
    printf("given[i]: (%d, %d)\n", validMoves6[i]->x, validMoves6[i]->y);
  }
  assert(retSize6 == 0);

  CE__movePiece(game, &(CE_Coord){2, 0}, &(CE_Coord){4, 4});
  size_t retSize7 = 0;
  CE_Coord **givenCoords = CE_getValidMoves(game, &(CE_Coord){4, 4}, &retSize7);
  CE_Coord c1 = {3, 3};
  CE_Coord c2 = {2, 2};
  CE_Coord c3 = {3, 5};
  CE_Coord c4 = {2, 6};
  CE_Coord c5 = {5, 5};
  CE_Coord c6 = {6, 6};
  CE_Coord c7 = {5, 3};
  CE_Coord c8 = {6, 2};
  CE_Coord *expectedC1[] = {
      &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8,
  };
  for (size_t i = 0; i < retSize7; ++i) {
    printf("given[i]: (%d, %d)\n", givenCoords[i]->x, givenCoords[i]->y);
  }
  assertValidMoves(expectedC1, 8, givenCoords, retSize7);

  // Reset board
  game->board = CE__createBoard();

  // Knight tests
  size_t givenSize = 0;
  CE_Coord **givenCoords1 = CE_getValidMoves(game, &(CE_Coord){1, 0}, &givenSize);

  CE_Coord k1 = {0, 2};
  CE_Coord k2 = {2, 2};

  CE_Coord *expectedK[] = {
      &k1,
      &k2,
  };

  assertValidMoves(expectedK, 2, givenCoords1, givenSize);

  CE__movePiece(game, &((CE_Coord){1, 0}), &((CE_Coord){4, 4}));

  size_t givenSize1 = 0;
  CE_Coord **givenCoords2 = CE_getValidMoves(game, &(CE_Coord){4, 4}, &givenSize1);

  CE_Coord k3 = {3, 2};
  CE_Coord k4 = {5, 2};
  CE_Coord k5 = {2, 3};
  CE_Coord k6 = {6, 3};
  CE_Coord k7 = {2, 5};
  CE_Coord k8 = {6, 5};
  CE_Coord k9 = {3, 6};
  CE_Coord k10 = {5, 6};

  CE_Coord *expectedK1[] = {
      &k3, &k4, &k5, &k6, &k7, &k8, &k9, &k10,
  };

  assertValidMoves(expectedK1, 8, givenCoords2, givenSize1);

  // Reset board
  game->board = CE__createBoard();

  // Queen test
  size_t retSize8 = 0;
  CE_getValidMoves(game, &(CE_Coord){3, 0}, &retSize8);
  // Assert that there are no valid moves
  assert(retSize8 == 0);

  CE__movePiece(game, &(CE_Coord){.x = 3, .y = 0}, &(CE_Coord){4, 4});
  size_t retSize9 = 0;
  CE_Coord **givenMoves4 = CE_getValidMoves(game, &(CE_Coord){4, 4}, &retSize9);
  CE_Coord q1 = {3, 4};
  CE_Coord q2 = {2, 4};
  CE_Coord q3 = {1, 4};
  CE_Coord q4 = {0, 4};
  CE_Coord q5 = {5, 4};
  CE_Coord q6 = {6, 4};
  CE_Coord q7 = {7, 4};
  CE_Coord q8 = {4, 3};
  CE_Coord q9 = {4, 2};
  CE_Coord q10 = {4, 5};
  CE_Coord q11 = {4, 6};
  CE_Coord q12 = {3, 3};
  CE_Coord q13 = {2, 2};
  CE_Coord q14 = {3, 5};
  CE_Coord q15 = {2, 6};
  CE_Coord q16 = {5, 5};
  CE_Coord q17 = {6, 6};
  CE_Coord q18 = {5, 3};
  CE_Coord q19 = {6, 2};
  CE_Coord *expected5[] = {
      &q1,  &q2,  &q3,  &q4,  &q5,  &q6,  &q7,  &q8,  &q9,  &q10,
      &q11, &q12, &q13, &q14, &q15, &q16, &q17, &q18, &q19,
  };
  CE__printBoard(game);
  for (size_t i = 0; i < retSize5; ++i) {
    printf("given[i]: (%d, %d)\n", givenMoves4[i]->x, givenMoves4[i]->y);
  }
  assertValidMoves(expected5, 19, givenMoves4, retSize9);

  // Reset board
  game->board = CE__createBoard();

  // King test
  size_t kingRetSize = 0;
  CE_getValidMoves(game, &(CE_Coord){4, 0}, &kingRetSize);
  assert(kingRetSize == 0);

  CE__movePiece(game, &(CE_Coord){4, 0}, &(CE_Coord){5, 5});
  CE__movePiece(game, &(CE_Coord){5, 7}, &(CE_Coord){1, 1});

  size_t kingRetSize2 = 0;
  CE_Coord **validKingMoves2 =
      CE_getValidMoves(game, &(CE_Coord){5, 5}, &kingRetSize2);

  CE_Coord king1 = {5, 4};
  CE_Coord king2 = {6, 4};

  CE_Coord *expectedKingMoves[] = {&king1, &king2};

  for (size_t i = 0; i < kingRetSize2; ++i) {
    printf("given[i]: (%d, %d)\n", givenMoves4[i]->x, givenMoves4[i]->y);
  }
  CE__printBoard(game);
  assertValidMoves(expectedKingMoves, 2, validKingMoves2, kingRetSize2);

  game->board = CE__createBoard();

  // Check for castling
  CE__movePiece(game, &(CE_Coord){3, 0}, &(CE_Coord){7, 7});
  CE__movePiece(game, &(CE_Coord){2, 0}, &(CE_Coord){7, 7});
  CE__movePiece(game, &(CE_Coord){1, 0}, &(CE_Coord){7, 7});
  CE__movePiece(game, &(CE_Coord){5, 0}, &(CE_Coord){7, 7});
  CE__movePiece(game, &(CE_Coord){6, 0}, &(CE_Coord){7, 7});
  size_t castlingMovesSize = 0;
  CE_Coord **validCastlingMoves =
      CE_getValidMoves(game, &(CE_Coord){4, 0}, &castlingMovesSize);
  CE_Coord castling1 = {3, 0};
  CE_Coord castling2 = {2, 0};
  CE_Coord castling3 = {5, 0};
  CE_Coord castling4 = {6, 0};
  CE_Coord *expectedCastlingMoves[] = {
      &castling1,
      &castling2,
      &castling3,
      &castling4,
  };
  for (size_t i = 0; i < castlingMovesSize; ++i) {
    printf("given[i]: (%d, %d)\n", validCastlingMoves[i]->x,
           validCastlingMoves[i]->y);
  }
  CE__printBoard(game);
  assertValidMoves(expectedCastlingMoves, 4, validCastlingMoves,
                   castlingMovesSize);
}

int main() {
  testCreateBoard();
  printf("Create Board test passed!\n");
  testMovePiece();
  printf("Move Piece test passed!\n");
  testIsCheck();
  printf("Is Check test passed!\n");
  testGetValidMoves();
  printf("Get valid moves test passed!\n");
  return EXIT_SUCCESS;
}
