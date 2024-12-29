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
  Game *game = initGame();
  SquareTypes **board = game->board;
  Coord *src = (Coord *)malloc(sizeof(Coord));
  Coord *dst = (Coord *)malloc(sizeof(Coord));

  // Move white king to the centre
  src->x = 4;
  src->y = 0;
  dst->x = 4;
  dst->y = 4;
  movePiece(board, src, dst);

  // Check all knight checks
  src->x = 6;
  src->y = 7;
  dst->x = 2;
  dst->y = 5;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 2;
  dst->y = 3;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 3;
  dst->y = 6;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 3;
  dst->y = 2;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 5;
  dst->y = 2;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 5;
  dst->y = 6;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 6;
  dst->y = 5;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 6;
  dst->y = 3;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  // Knight check cleanup
  src->x = dst->x;
  src->y = dst->y;
  dst->x = 6;
  dst->y = 7;
  movePiece(board, src, dst);

  // Pawn Checks
  src->x = 0;
  src->y = 6;
  dst->x = 3;
  dst->y = 5;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 5;
  dst->y = 5;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 3;
  dst->y = 3;
  movePiece(board, src, dst);

  assert(!isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 5;
  dst->y = 3;
  movePiece(board, src, dst);

  assert(!isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 0;
  dst->y = 6;
  movePiece(board, src, dst);

  src->x = 0;
  src->y = 1;
  dst->x = 3;
  dst->y = 5;
  movePiece(board, src, dst);

  assert(!isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 5;
  dst->y = 5;
  movePiece(board, src, dst);

  assert(!isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 7;
  dst->y = 7;
  movePiece(board, src, dst);

  assert(!isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 5;
  dst->y = 7;
  movePiece(board, src, dst);

  assert(!isCheck(game, WHITE));

  // Pawn Cleanup
  src->x = dst->x;
  src->y = dst->y;
  dst->x = 0;
  dst->y = 6;
  movePiece(board, src, dst);

  // Piece used to test if blocking a check with a piece works
  Coord *blockPieceSrc = (Coord *)malloc(sizeof(Coord));
  Coord *blockPieceDst = (Coord *)malloc(sizeof(Coord));

  // Bishop Checks
  src->x = 2;
  src->y = 7;
  dst->x = 1;
  dst->y = 1;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  blockPieceSrc->x = 2;
  blockPieceSrc->y = 1;
  blockPieceDst->x = 2;
  blockPieceDst->y = 2;
  movePiece(board, blockPieceSrc, blockPieceDst);

  assert(!isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 6;
  dst->y = 6;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 5;
  blockPieceDst->y = 5;
  movePiece(board, blockPieceSrc, blockPieceDst);

  assert(!isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 2;
  dst->y = 6;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 3;
  blockPieceDst->y = 5;
  movePiece(board, blockPieceSrc, blockPieceDst);

  assert(!isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 7;
  dst->y = 1;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 6;
  blockPieceDst->y = 2;
  movePiece(board, blockPieceSrc, blockPieceDst);

  assert(!isCheck(game, WHITE));

  // Cleanup
  src->x = dst->x;
  src->y = dst->y;
  dst->x = 0;
  dst->y = 0;
  movePiece(board, src, dst);

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 1;
  blockPieceDst->y = 0;
  movePiece(board, blockPieceSrc, blockPieceDst);

  // Rook Checks
  src->x = 0;
  src->y = 7;
  dst->x = 0;
  dst->y = 4;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 1;
  blockPieceDst->y = 4;
  movePiece(board, blockPieceSrc, blockPieceDst);

  assert(!isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 7;
  dst->y = 4;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 6;
  blockPieceDst->y = 4;
  movePiece(board, blockPieceSrc, blockPieceDst);

  assert(!isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 4;
  dst->y = 6;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 4;
  blockPieceDst->y = 5;
  movePiece(board, blockPieceSrc, blockPieceDst);

  assert(!isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 4;
  dst->y = 1;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 4;
  blockPieceDst->y = 2;
  movePiece(board, blockPieceSrc, blockPieceDst);

  assert(!isCheck(game, WHITE));

  // Clean Up
  src->x = dst->x;
  src->y = dst->y;
  dst->x = 0;
  dst->y = 0;
  movePiece(board, src, dst);

  // Queen check
  // Diagonal checks
  src->x = 3;
  src->y = 7;
  dst->x = 1;
  dst->y = 1;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 2;
  blockPieceDst->y = 2;
  movePiece(board, blockPieceSrc, blockPieceDst);

  assert(!isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 6;
  dst->y = 6;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 5;
  blockPieceDst->y = 5;
  movePiece(board, blockPieceSrc, blockPieceDst);

  assert(!isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 2;
  dst->y = 6;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 3;
  blockPieceDst->y = 5;
  movePiece(board, blockPieceSrc, blockPieceDst);

  assert(!isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 7;
  dst->y = 1;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 6;
  blockPieceDst->y = 2;
  movePiece(board, blockPieceSrc, blockPieceDst);
  assert(!isCheck(game, WHITE));

  // Straight check
  src->x = dst->x;
  src->y = dst->y;
  dst->x = 0;
  dst->y = 4;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 1;
  blockPieceDst->y = 4;
  movePiece(board, blockPieceSrc, blockPieceDst);

  assert(!isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 7;
  dst->y = 4;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 6;
  blockPieceDst->y = 4;
  movePiece(board, blockPieceSrc, blockPieceDst);

  assert(!isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 4;
  dst->y = 6;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 4;
  blockPieceDst->y = 5;
  movePiece(board, blockPieceSrc, blockPieceDst);

  assert(!isCheck(game, WHITE));

  src->x = dst->x;
  src->y = dst->y;
  dst->x = 4;
  dst->y = 1;
  movePiece(board, src, dst);

  assert(isCheck(game, WHITE));

  blockPieceSrc->x = blockPieceDst->x;
  blockPieceSrc->y = blockPieceDst->y;
  blockPieceDst->x = 4;
  blockPieceDst->y = 2;
  movePiece(board, blockPieceSrc, blockPieceDst);
  assert(!isCheck(game, WHITE));
}

void assertValidMoves(Coord **expected, size_t expectedSize, Coord **given,
                      size_t givenSize) {
  printf("expectedSize: %zu, givenSize: %zu\n", expectedSize, givenSize);
  assert(expectedSize == givenSize);
  for (size_t i = 0; i < givenSize; ++i) {
    assert(given[i] != NULL);
    assert(expected[i] != NULL);
  }
  for (size_t i = 0; i < givenSize; ++i) {
    Coord *givenCoord = given[i];
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
  Game *game = initGame();
  size_t retSize = 0;
  Coord **validMoves = getValidMoves(game, &(Coord){0, 1}, &retSize);
  printf("Valid moves:\n");
  for (size_t i = 0; i < retSize; ++i) {
    printf("(%d, %d)\n", validMoves[i]->x, validMoves[i]->y);
  }
  Coord e1 = {0, 2};
  // Long jump
  Coord e2 = {0, 3};
  Coord *expected[] = {
      &e1,
      &e2,
  };
  assertValidMoves(expected, 2, validMoves, retSize);

  movePiece(game->board, &(Coord){0, 1}, &(Coord){1, 5});
  size_t retSize2 = 0;
  Coord **validMoves2 = getValidMoves(game, &(Coord){1, 5}, &retSize2);
  printf("Valid moves:\n");
  for (size_t i = 0; i < retSize2; ++i) {
    printf("(%d, %d)\n", validMoves2[i]->x, validMoves2[i]->y);
  }

  Coord e3 = {0, 6};
  Coord e4 = {2, 6};
  Coord *expected2[] = {
      &e3,
      &e4,
  };
  assertValidMoves(expected2, 2, validMoves2, retSize2);

  // Test for en passant
  movePiece(game->board, &(Coord){1, 5}, &(Coord){1, 4});
  movePiece(game->board, &(Coord){2, 6}, &(Coord){2, 4});
  game->enPassantSquare = &(Coord){2, 5};

  size_t retSize3 = 0;
  Coord **validMoves3 = getValidMoves(game, &(Coord){1, 4}, &retSize3);

  for (size_t i = 0; i < retSize3; ++i) {
    printf("(%d, %d)\n", validMoves3[i]->x, validMoves3[i]->y);
  }
  Coord e5 = {1, 5};
  Coord e6 = {2, 5};
  Coord *expected3[] = {
      &e5,
      &e6,
  };
  assertValidMoves(expected3, 2, validMoves3, retSize3);

  // Reset board
  game->board = createBoard();

  // Rook Tests
  size_t retSize4 = 0;
  movePiece(game->board, &(Coord){0, 0}, &(Coord){3, 0});
  Coord **validMoves4 = getValidMoves(game, &(Coord){0, 0}, &retSize4);
  // Assert that there are no valid moves
  assert(retSize4 == 0);

  movePiece(game->board, &(Coord){3, 0}, &(Coord){4, 4});
  size_t retSize5 = 0;
  Coord **validMoves5 = getValidMoves(game, &(Coord){4, 4}, &retSize5);
  Coord e7 = {3, 4};
  Coord e8 = {2, 4};
  Coord e9 = {1, 4};
  Coord e10 = {0, 4};
  Coord e11 = {5, 4};
  Coord e12 = {6, 4};
  Coord e13 = {7, 4};
  Coord e14 = {4, 3};
  Coord e15 = {4, 2};
  Coord e16 = {4, 5};
  Coord e17 = {4, 6};
  Coord *expected4[] = {
      &e7, &e8, &e9, &e10, &e11, &e12, &e13, &e14, &e15, &e16, &e17,
  };
  printBoard(game);
  for (size_t i = 0; i < retSize5; ++i) {
    printf("given[i]: (%d, %d)\n", validMoves5[i]->x, validMoves5[i]->y);
  }
  assertValidMoves(expected4, 11, validMoves5, retSize5);

  // Reset board
  game->board = createBoard();

  // Bishop tests
  size_t retSize6 = 0;
  Coord **validMoves6 = getValidMoves(game, &(Coord){2, 0}, &retSize6);
  // Assert that there are no valid moves
  printBoard(game);
  for (size_t i = 0; i < retSize6; ++i) {
    printf("given[i]: (%d, %d)\n", validMoves6[i]->x, validMoves6[i]->y);
  }
  assert(retSize6 == 0);

  movePiece(game->board, &(Coord){2, 0}, &(Coord){4, 4});
  size_t retSize7 = 0;
  Coord **givenCoords = getValidMoves(game, &(Coord){4, 4}, &retSize7);
  Coord c1 = {3, 3};
  Coord c2 = {2, 2};
  Coord c3 = {3, 5};
  Coord c4 = {2, 6};
  Coord c5 = {5, 5};
  Coord c6 = {6, 6};
  Coord c7 = {5, 3};
  Coord c8 = {6, 2};
  Coord *expectedC1[] = {
      &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8,
  };
  for (size_t i = 0; i < retSize7; ++i) {
    printf("given[i]: (%d, %d)\n", givenCoords[i]->x, givenCoords[i]->y);
  }
  assertValidMoves(expectedC1, 8, givenCoords, retSize7);

  // Reset board
  game->board = createBoard();

  // Knight tests
  size_t givenSize = 0;
  Coord **givenCoords1 = getValidMoves(game, &(Coord){1, 0}, &givenSize);

  Coord k1 = {0, 2};
  Coord k2 = {2, 2};

  Coord *expectedK[] = {
      &k1,
      &k2,
  };

  assertValidMoves(expectedK, 2, givenCoords1, givenSize);

  movePiece(game->board, &((Coord){1, 0}), &((Coord){4, 4}));

  size_t givenSize1 = 0;
  Coord **givenCoords2 = getValidMoves(game, &(Coord){4, 4}, &givenSize1);

  Coord k3 = {3, 2};
  Coord k4 = {5, 2};
  Coord k5 = {2, 3};
  Coord k6 = {6, 3};
  Coord k7 = {2, 5};
  Coord k8 = {6, 5};
  Coord k9 = {3, 6};
  Coord k10 = {5, 6};

  Coord *expectedK1[] = {
      &k3, &k4, &k5, &k6, &k7, &k8, &k9, &k10,
  };

  assertValidMoves(expectedK1, 8, givenCoords2, givenSize1);

  // Reset board
  game->board = createBoard();

  // Queen test
  size_t retSize8 = 0;
  Coord **givenMoves3 = getValidMoves(game, &(Coord){3, 0}, &retSize8);
  // Assert that there are no valid moves
  assert(retSize8 == 0);

  movePiece(game->board, &(Coord){.x = 3, .y = 0}, &(Coord){4, 4});
  size_t retSize9 = 0;
  Coord **givenMoves4 = getValidMoves(game, &(Coord){4, 4}, &retSize9);
  Coord q1 = {3, 4};
  Coord q2 = {2, 4};
  Coord q3 = {1, 4};
  Coord q4 = {0, 4};
  Coord q5 = {5, 4};
  Coord q6 = {6, 4};
  Coord q7 = {7, 4};
  Coord q8 = {4, 3};
  Coord q9 = {4, 2};
  Coord q10 = {4, 5};
  Coord q11 = {4, 6};
  Coord q12 = {3, 3};
  Coord q13 = {2, 2};
  Coord q14 = {3, 5};
  Coord q15 = {2, 6};
  Coord q16 = {5, 5};
  Coord q17 = {6, 6};
  Coord q18 = {5, 3};
  Coord q19 = {6, 2};
  Coord *expected5[] = {
      &q1,  &q2,  &q3,  &q4,  &q5,  &q6,  &q7,  &q8,  &q9,  &q10,
      &q11, &q12, &q13, &q14, &q15, &q16, &q17, &q18, &q19,
  };
  printBoard(game);
  for (size_t i = 0; i < retSize5; ++i) {
    printf("given[i]: (%d, %d)\n", givenMoves4[i]->x, givenMoves4[i]->y);
  }
  assertValidMoves(expected5, 19, givenMoves4, retSize9);

  // Reset board
  game->board = createBoard();

  // King test
  size_t kingRetSize = 0;
  Coord **validKingMoves = getValidMoves(game, &(Coord){4, 0}, &kingRetSize);
  assert(kingRetSize == 0);

  movePiece(game->board, &(Coord){4, 0}, &(Coord){5, 5});
  movePiece(game->board, &(Coord){5, 7}, &(Coord){1, 1});

  size_t kingRetSize2 = 0;
  Coord **validKingMoves2 = getValidMoves(game, &(Coord){5, 5}, &kingRetSize2);

  Coord king1 = {5, 4};
  Coord king2 = {6, 4};

  Coord *expectedKingMoves[] = {&king1, &king2};

  for (size_t i = 0; i < kingRetSize2; ++i) {
    printf("given[i]: (%d, %d)\n", givenMoves4[i]->x, givenMoves4[i]->y);
  }
  printBoard(game);
  assertValidMoves(expectedKingMoves, 2, validKingMoves2, kingRetSize2);

  game->board = createBoard();

  // Check for castling
  movePiece(game->board, &(Coord){3, 0}, &(Coord){7, 7});
  movePiece(game->board, &(Coord){2, 0}, &(Coord){7, 7});
  movePiece(game->board, &(Coord){1, 0}, &(Coord){7, 7});
  movePiece(game->board, &(Coord){5, 0}, &(Coord){7, 7});
  movePiece(game->board, &(Coord){6, 0}, &(Coord){7, 7});
  size_t castlingMovesSize = 0;
  Coord **validCastlingMoves =
      getValidMoves(game, &(Coord){4, 0}, &castlingMovesSize);
  Coord castling1 = {3, 0};
  Coord castling2 = {2, 0};
  Coord castling3 = {5, 0};
  Coord castling4 = {6, 0};
  Coord *expectedCastlingMoves[] = {
    &castling1, &castling2, &castling3, &castling4,
  };
  for (size_t i = 0; i < castlingMovesSize; ++i) {
    printf("given[i]: (%d, %d)\n", validCastlingMoves[i]->x, validCastlingMoves[i]->y);
  }
  printBoard(game);
  assertValidMoves(expectedCastlingMoves, 4, validCastlingMoves, castlingMovesSize);
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
