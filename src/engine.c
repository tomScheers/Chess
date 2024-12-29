#include "engine.h"
#include "engine_internal.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

CE_Game *CE_initGame() {
  CE_Game *game = (CE_Game *)malloc(sizeof(CE_Game));
  game->board = CE__createBoard();
  game->currPlayer = CE_WHITE_PLAYER;
  game->whiteHasCastleRight[0] = true;
  game->whiteHasCastleRight[1] = true;
  game->blackHasCastleRight[0] = true;
  game->blackHasCastleRight[1] = true;
  game->enPassantSquare = (CE_Coord *)malloc(sizeof(CE_Coord));
  game->enPassantSquare->y = -1;
  game->enPassantSquare->x = -1;
  return game;
}

bool CE_makeValidMove(CE_Game *game, CE_Coord *src, CE_Coord *dst) {
  size_t validMovesSize = 0;
  CE_Coord **validSrcMoves = CE_getValidMoves(game, src, &validMovesSize);
  bool isValidMove = false;
  for (size_t i = 0; i < validMovesSize; ++i) {
    if (validSrcMoves[i]->x == dst->x && validSrcMoves[i]->y == dst->y) {
      isValidMove = true;
      break;
    }
  }
  if (!isValidMove)
    return false;

  if (game->currPlayer != CE__getPlayer(&game->board[src->y][src->x]))
    return false;

  switch (game->board[src->y][src->x]) {
  case CE_BLACK_PAWN:
  case CE_WHITE_PAWN:
    if (dst->y - src->y == 2) {
      game->enPassantSquare->x = dst->x;
      game->enPassantSquare->y = dst->y - 1;
    }
    break;
  case CE_BLACK_KING:
  case CE_WHITE_KING:
    if (game->currPlayer == CE_WHITE_PLAYER) {
      game->whiteHasCastleRight[0] = false;
      game->whiteHasCastleRight[1] = false;
    } else {
      game->blackHasCastleRight[0] = false;
      game->blackHasCastleRight[1] = false;
    }
    break;
  case CE_BLACK_ROOK:
  case CE_WHITE_ROOK:
    if (game->currPlayer == CE_WHITE_PLAYER) {
      if (src->x == 0) {
        game->whiteHasCastleRight[0] = false;
      } else if (src->x == 7) {
        game->whiteHasCastleRight[0] = false;
      }
    } else {
      if (src->x == 0) {
        game->blackHasCastleRight[0] = false;
      } else if (src->x == 7) {
        game->blackHasCastleRight[0] = false;
      }
    }
    break;
  default:
    break;
  }
  CE__movePiece(game, src, dst);
  game->currPlayer = game->currPlayer == CE_WHITE_PLAYER ? CE_BLACK_PLAYER : CE_WHITE_PLAYER;
  return true;
}

CE_Coord **CE_getValidMoves(CE_Game *game, CE_Coord *pieceToMove,
                            size_t *returnSize) {
  CE_SquareTypes **board = game->board;
  CE_Coord **validMoves =
      malloc(100 * sizeof(CE_Coord *)); // Adjust size as needed
  size_t validMovesIndex = 0;
  int yOrigin = pieceToMove->y;
  int xOrigin = pieceToMove->x;

  // This will be used to check if a piece on a square is on the same team as
  // the piece to move if not, you can capture
  CE_Player currPlayer = CE__getPlayer(&board[pieceToMove->y][pieceToMove->x]);

  if (currPlayer == CE_NO_PLAYER) {
    printf("Invalid square\n");
    printf("Square: %d\n", currPlayer);
    return validMoves;
  }

  CE_Player oppPlayer =
      currPlayer == CE_WHITE_PLAYER ? CE_BLACK_PLAYER : CE_WHITE_PLAYER;
  int pawnIncrement = currPlayer == CE_WHITE_PLAYER ? 1 : -1;
  CE__printBoard(game);
  switch (board[yOrigin][xOrigin]) {
  case CE_EMPTY:
    break;
  case CE_WHITE_PAWN:
  case CE_BLACK_PAWN:
    if (board[yOrigin + pawnIncrement][xOrigin] == CE_EMPTY &&
        !CE__isCheck(
            CE__cpMovePiece(game, pieceToMove,
                            &(CE_Coord){xOrigin, yOrigin + pawnIncrement}),
            currPlayer)) {
      validMoves[validMovesIndex] = (CE_Coord *)malloc(sizeof(CE_Coord));
      validMoves[validMovesIndex]->y = yOrigin + pawnIncrement;
      validMoves[validMovesIndex]->x = xOrigin;
      ++validMovesIndex;
    }

    bool canEnPassant1 = game->enPassantSquare != NULL &&
                         xOrigin + 1 == game->enPassantSquare->x &&
                         yOrigin + pawnIncrement == game->enPassantSquare->y;
    bool canCapture1 =
        CE__getPlayer(&game->board[yOrigin + pawnIncrement][xOrigin + 1]) ==
        oppPlayer;

    if (CE__isInRange(xOrigin + 1, yOrigin + pawnIncrement) &&
        (canCapture1 || canEnPassant1) &&
        !CE__isCheck(
            CE__cpMovePiece(game, pieceToMove,
                            &(CE_Coord){xOrigin + 1, yOrigin + pawnIncrement}),
            CE__getPlayer(&game->board[pieceToMove->y][pieceToMove->x]))) {
      validMoves[validMovesIndex] = (CE_Coord *)malloc(sizeof(CE_Coord));
      validMoves[validMovesIndex]->y = yOrigin + pawnIncrement;
      validMoves[validMovesIndex]->x = xOrigin + 1;
      ++validMovesIndex;
    }

    bool canEnPassant2 = xOrigin - 1 == game->enPassantSquare->x &&
                         yOrigin + pawnIncrement == game->enPassantSquare->y;
    bool canCapture2 =
        CE__getPlayer(&game->board[yOrigin + pawnIncrement][xOrigin - 1]) ==
        oppPlayer;

    if (CE__isInRange(xOrigin - 1, yOrigin + pawnIncrement) &&
        (canEnPassant2 || canCapture2) &&
        !CE__isCheck(
            CE__cpMovePiece(game, pieceToMove,
                            &(CE_Coord){xOrigin - 1, yOrigin + pawnIncrement}),
            CE__getPlayer(&game->board[pieceToMove->y][pieceToMove->x]))) {
      validMoves[validMovesIndex] = (CE_Coord *)malloc(sizeof(CE_Coord));
      validMoves[validMovesIndex]->y = yOrigin + pawnIncrement;
      validMoves[validMovesIndex]->x = xOrigin - 1;
      ++validMovesIndex;
    }

    if (CE__isInRange(xOrigin, yOrigin + pawnIncrement * 2) &&
        game->board[yOrigin + pawnIncrement * 2][xOrigin] == CE_EMPTY &&
        yOrigin == (currPlayer == CE_WHITE_PLAYER ? 1 : 6)) {

      validMoves[validMovesIndex] = (CE_Coord *)malloc(sizeof(CE_Coord));
      validMoves[validMovesIndex]->y = yOrigin + pawnIncrement * 2;
      validMoves[validMovesIndex]->x = xOrigin;
      ++validMovesIndex;
    }

    break;

  case CE_WHITE_ROOK:
  case CE_BLACK_ROOK:
    for (int x = pieceToMove->x - 1; x >= 0; --x) {
      if (!CE__canMoveTo(game, pieceToMove, &(CE_Coord){x, yOrigin}, validMoves,
                         &validMovesIndex))
        break;
    }

    for (int x = pieceToMove->x + 1; x < 8; ++x) {
      if (!CE__canMoveTo(game, pieceToMove, &(CE_Coord){x, yOrigin}, validMoves,
                         &validMovesIndex))
        break;
    }

    for (int y = pieceToMove->y - 1; y >= 0; --y) {
      if (!CE__canMoveTo(game, pieceToMove, &(CE_Coord){xOrigin, y}, validMoves,
                         &validMovesIndex))
        break;
    }

    for (int y = pieceToMove->y + 1; y < 8; ++y) {
      if (!CE__canMoveTo(game, pieceToMove, &(CE_Coord){xOrigin, y}, validMoves,
                         &validMovesIndex))
        break;
    }
    break;

  case CE_WHITE_BISHOP:
  case CE_BLACK_BISHOP:
    for (int i = 1; i < 7 - xOrigin; ++i) {
      if (!CE__canMoveTo(game, pieceToMove,
                         &(CE_Coord){xOrigin + i, yOrigin + i}, validMoves,
                         &validMovesIndex))
        break;
    }

    for (int i = 1; i < 7 - xOrigin; ++i) {
      if (!CE__canMoveTo(game, pieceToMove,
                         &(CE_Coord){xOrigin + i, yOrigin - i}, validMoves,
                         &validMovesIndex))
        break;
    }

    for (int i = 1; i < xOrigin; ++i) {
      if (!CE__canMoveTo(game, pieceToMove,
                         &(CE_Coord){xOrigin - i, yOrigin - i}, validMoves,
                         &validMovesIndex))
        break;
    }

    for (int i = 1; i < xOrigin; ++i) {
      if (!CE__canMoveTo(game, pieceToMove,
                         &(CE_Coord){xOrigin - i, yOrigin + i}, validMoves,
                         &validMovesIndex))
        break;
    }

    break;
  case CE_WHITE_KING:
  case CE_BLACK_KING:
    for (int i = -1; i <= 1; ++i) {
      for (int j = -1; j <= 1; ++j) {
        int x = xOrigin + i;
        int y = yOrigin + j;
        CE__canMoveTo(game, pieceToMove, &(CE_Coord){x, y}, validMoves,
                      &validMovesIndex);
      }
    }
    bool *hasCastlingRights = currPlayer == CE_WHITE_PLAYER
                                  ? game->whiteHasCastleRight
                                  : game->blackHasCastleRight;

    CE_SquareTypes playerRook =
        currPlayer == CE_WHITE_PLAYER ? CE_WHITE_ROOK : CE_BLACK_ROOK;

    bool canReachRook1 = game->board[yOrigin][xOrigin + 1] == CE_EMPTY &&
                         game->board[yOrigin][xOrigin + 2] == CE_EMPTY;
    bool isInCheck1 =
        CE__isCheck(CE__cpMovePiece(game, pieceToMove,
                                    &(CE_Coord){xOrigin + 1, yOrigin}),
                    currPlayer) &&
        CE__isCheck(CE__cpMovePiece(game, pieceToMove,
                                    &(CE_Coord){xOrigin + 2, yOrigin}),
                    currPlayer);

    if (canReachRook1 && !isInCheck1 && hasCastlingRights[1]) {
      validMoves[validMovesIndex] = (CE_Coord *)malloc(sizeof(CE_Coord));
      validMoves[validMovesIndex]->x = xOrigin + 2;
      validMoves[validMovesIndex]->y = yOrigin;
      ++validMovesIndex;
    }

    bool canReachRook2 = game->board[yOrigin][xOrigin - 1] == CE_EMPTY &&
                         game->board[yOrigin][xOrigin - 2] == CE_EMPTY &&
                         game->board[yOrigin][xOrigin - 3] == CE_EMPTY;
    bool isInCheck2 =
        CE__isCheck(CE__cpMovePiece(game, pieceToMove,
                                    &(CE_Coord){xOrigin + 1, yOrigin}),
                    currPlayer) &&
        CE__isCheck(CE__cpMovePiece(game, pieceToMove,
                                    &(CE_Coord){xOrigin + 2, yOrigin}),
                    currPlayer);

    if (canReachRook2 && !isInCheck2 && hasCastlingRights[0]) {
      validMoves[validMovesIndex] = (CE_Coord *)malloc(sizeof(CE_Coord));
      validMoves[validMovesIndex]->x = xOrigin - 2;
      validMoves[validMovesIndex]->y = yOrigin;
      ++validMovesIndex;
    }

    break;
  case CE_WHITE_KNIGHT:
  case CE_BLACK_KNIGHT:
    CE__canMoveTo(game, pieceToMove, &(CE_Coord){xOrigin + 2, yOrigin + 1},
                  validMoves, &validMovesIndex);
    CE__canMoveTo(game, pieceToMove, &(CE_Coord){xOrigin + 2, yOrigin - 1},
                  validMoves, &validMovesIndex);
    CE__canMoveTo(game, pieceToMove, &(CE_Coord){xOrigin - 2, yOrigin + 1},
                  validMoves, &validMovesIndex);
    CE__canMoveTo(game, pieceToMove, &(CE_Coord){xOrigin - 2, yOrigin - 1},
                  validMoves, &validMovesIndex);
    CE__canMoveTo(game, pieceToMove, &(CE_Coord){xOrigin + 1, yOrigin + 2},
                  validMoves, &validMovesIndex);
    CE__canMoveTo(game, pieceToMove, &(CE_Coord){xOrigin + 1, yOrigin - 2},
                  validMoves, &validMovesIndex);
    CE__canMoveTo(game, pieceToMove, &(CE_Coord){xOrigin - 1, yOrigin + 2},
                  validMoves, &validMovesIndex);
    CE__canMoveTo(game, pieceToMove, &(CE_Coord){xOrigin - 1, yOrigin - 2},
                  validMoves, &validMovesIndex);
    break;
  case CE_WHITE_QUEEN:
  case CE_BLACK_QUEEN:
    for (int i = 1; i < 7 - xOrigin; ++i) {
      if (!CE__canMoveTo(game, pieceToMove,
                         &(CE_Coord){xOrigin + i, yOrigin + i}, validMoves,
                         &validMovesIndex))
        break;
    }

    for (int i = 1; i < 7 - xOrigin; ++i) {
      if (!CE__canMoveTo(game, pieceToMove,
                         &(CE_Coord){xOrigin + i, yOrigin - i}, validMoves,
                         &validMovesIndex))
        break;
    }

    for (int i = 1; i < xOrigin; ++i) {
      if (!CE__canMoveTo(game, pieceToMove,
                         &(CE_Coord){xOrigin - i, yOrigin - i}, validMoves,
                         &validMovesIndex))
        break;
    }

    for (int i = 1; i < xOrigin; ++i) {
      if (!CE__canMoveTo(game, pieceToMove,
                         &(CE_Coord){xOrigin - i, yOrigin + i}, validMoves,
                         &validMovesIndex))
        break;
    }

    for (int x = pieceToMove->x - 1; x >= 0; --x) {
      if (!CE__canMoveTo(game, pieceToMove, &(CE_Coord){x, yOrigin}, validMoves,
                         &validMovesIndex))
        break;
    }

    for (int x = pieceToMove->x + 1; x < 8; ++x) {
      if (!CE__canMoveTo(game, pieceToMove, &(CE_Coord){x, yOrigin}, validMoves,
                         &validMovesIndex))
        break;
    }

    for (int y = pieceToMove->y - 1; y >= 0; --y) {
      if (!CE__canMoveTo(game, pieceToMove, &(CE_Coord){xOrigin, y}, validMoves,
                         &validMovesIndex))
        break;
    }

    for (int y = pieceToMove->y + 1; y < 8; ++y) {
      if (!CE__canMoveTo(game, pieceToMove, &(CE_Coord){xOrigin, y}, validMoves,
                         &validMovesIndex))
        break;
    }

    break;
  }
  *returnSize = validMovesIndex;
  return validMoves;
}

bool CE__isInRange(int x, int y) { return y >= 0 && y < 8 && x >= 0 && x < 8; }

CE_SquareTypes **CE__createBoard() {
  CE_SquareTypes **board =
      (CE_SquareTypes **)malloc(sizeof(CE_SquareTypes *) * 8);
  for (int i = 0; i < 8; ++i) {
    board[i] = (CE_SquareTypes *)malloc(sizeof(CE_SquareTypes) * 8);
  }
  board[0][0] = CE_WHITE_ROOK;
  board[0][1] = CE_WHITE_KNIGHT;
  board[0][2] = CE_WHITE_BISHOP;
  board[0][3] = CE_WHITE_QUEEN;
  board[0][4] = CE_WHITE_KING;
  board[0][5] = CE_WHITE_BISHOP;
  board[0][6] = CE_WHITE_KNIGHT;
  board[0][7] = CE_WHITE_ROOK;
  board[7][0] = CE_BLACK_ROOK;
  board[7][1] = CE_BLACK_KNIGHT;
  board[7][2] = CE_BLACK_BISHOP;
  board[7][3] = CE_BLACK_QUEEN;
  board[7][4] = CE_BLACK_KING;
  board[7][5] = CE_BLACK_BISHOP;
  board[7][6] = CE_BLACK_KNIGHT;
  board[7][7] = CE_BLACK_ROOK;
  for (int i = 0; i < 8; ++i) {
    board[1][i] = CE_WHITE_PAWN;
    board[6][i] = CE_BLACK_PAWN;
  }
  for (int i = 2; i < 6; ++i) {
    for (int j = 0; j < 8; ++j) {
      board[i][j] = CE_EMPTY;
    }
  }
  return board;
}

void CE__printBoard(CE_Game *game) {
  CE_SquareTypes **board = game->board;
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      switch (board[i][j]) {
      case CE_WHITE_ROOK:
      case CE_BLACK_ROOK:
        printf("Rook ");
        break;
      case CE_WHITE_KNIGHT:
      case CE_BLACK_KNIGHT:
        printf("Knight ");
        break;
      case CE_WHITE_BISHOP:
      case CE_BLACK_BISHOP:
        printf("Bishop ");
        break;
      case CE_WHITE_QUEEN:
      case CE_BLACK_QUEEN:
        printf("Queen ");
        break;
      case CE_WHITE_KING:
      case CE_BLACK_KING:
        printf("King ");
        break;
      case CE_WHITE_PAWN:
      case CE_BLACK_PAWN:
        printf("Pawn ");
        break;
      case CE_EMPTY:
        printf("Empty ");
        break;
      }
    }
    printf("\n");
  }
}

bool CE__isCheck(CE_Game *game, CE_Player player) {
  CE_SquareTypes **board = game->board;
  CE_SquareTypes king =
      player == CE_WHITE_PLAYER ? CE_WHITE_KING : CE_BLACK_KING;
  CE_SquareTypes oposingRook =
      player == CE_WHITE_PLAYER ? CE_BLACK_ROOK : CE_WHITE_ROOK;
  CE_SquareTypes oposingQueen =
      player == CE_WHITE_PLAYER ? CE_BLACK_QUEEN : CE_WHITE_QUEEN;
  CE_SquareTypes oposingBishop =
      player == CE_WHITE_PLAYER ? CE_BLACK_BISHOP : CE_WHITE_BISHOP;
  CE_SquareTypes oposingPawn =
      player == CE_WHITE_PLAYER ? CE_BLACK_PAWN : CE_WHITE_PAWN;
  CE_SquareTypes oposingKnight =
      player == CE_WHITE_PLAYER ? CE_BLACK_KNIGHT : CE_WHITE_KNIGHT;
  CE_SquareTypes oposingKing =
      player == CE_WHITE_PLAYER ? CE_BLACK_KING : CE_WHITE_KING;

  // Black's pawns move 'downwards' from the arrays perspective, so the program
  // needs to take that into acount
  int moveIncrement = player == CE_WHITE_PLAYER ? 1 : -1;

  CE_Coord *kingCoords = (CE_Coord *)malloc(sizeof(CE_Coord));
  kingCoords->y = -1;
  kingCoords->x = -1;
  for (int y = 0; y < 8; ++y) {
    for (int x = 0; x < 8; ++x) {
      if (board[y][x] == king) {
        kingCoords->y = y;
        kingCoords->x = x;
        break;
      }
    }
    if (kingCoords->y != -1)
      break;
  }

  if (kingCoords->y == -1) {
    CE__printBoard(game);
    fprintf(stderr, "No kingcoords\n");
    exit(EXIT_FAILURE);
  }

  // Check for horizontal queen and rook checks
  // Check from right-hand side
  for (int x = kingCoords->x + 1; x < 8; ++x) {
    if (board[kingCoords->y][x] == oposingRook ||
        board[kingCoords->y][x] == oposingQueen)
      return true;
    if (board[kingCoords->y][x] != CE_EMPTY)
      break;
  }
  // Check from left-hand side
  for (int x = kingCoords->x - 1; x >= 0; --x) {
    if (board[kingCoords->y][x] == oposingRook ||
        board[kingCoords->y][x] == oposingQueen)
      return true;
    if (board[kingCoords->y][x] != CE_EMPTY)
      break;
  }

  // Check for vertical queen and rook checks
  // Check from right-hand side
  for (int y = kingCoords->y - 1; y >= 0; --y) {
    if (board[y][kingCoords->x] == oposingRook ||
        board[y][kingCoords->x] == oposingQueen)
      return true;
    if (board[y][kingCoords->x] != CE_EMPTY)
      break;
  }
  // Check from left-hand side
  for (int y = kingCoords->y + 1; y < 8; ++y) {
    if (board[y][kingCoords->x] == oposingRook ||
        board[y][kingCoords->x] == oposingQueen)
      return true;
    if (board[y][kingCoords->x] != CE_EMPTY)
      break;
  }

  // Check pawn checks
  if ((CE__isInRange(kingCoords->x + 1, kingCoords->y + moveIncrement) &&
       board[kingCoords->y + moveIncrement][kingCoords->x + 1] ==
           oposingPawn) ||
      (CE__isInRange(kingCoords->x - 1, kingCoords->y + moveIncrement) &&
       board[kingCoords->y + moveIncrement][kingCoords->x - 1] == oposingPawn))
    return true;

  // Check for knight checks
  if (CE__isInRange(kingCoords->x + 1, kingCoords->y + 2) &&
      board[kingCoords->y + 2][kingCoords->x + 1] == oposingKnight)
    return true;

  if (CE__isInRange(kingCoords->x - 1, kingCoords->y + 2) &&
      board[kingCoords->y + 2][kingCoords->x - 1] == oposingKnight)
    return true;

  if (CE__isInRange(kingCoords->x - 2, kingCoords->y + 1) &&
      board[kingCoords->y + 1][kingCoords->x - 2] == oposingKnight)
    return true;

  if (CE__isInRange(kingCoords->x - 2, kingCoords->y - 1) &&
      board[kingCoords->y - 1][kingCoords->x - 2] == oposingKnight)
    return true;

  if (CE__isInRange(kingCoords->x + 1, kingCoords->y - 2) &&
      board[kingCoords->y - 2][kingCoords->x + 1] == oposingKnight)
    return true;

  if (CE__isInRange(kingCoords->x - 1, kingCoords->y - 2) &&
      board[kingCoords->y - 2][kingCoords->x - 1] == oposingKnight)
    return true;

  if (CE__isInRange(kingCoords->x + 2, kingCoords->y + 1) &&
      board[kingCoords->y + 1][kingCoords->x + 2] == oposingKnight)
    return true;

  if (CE__isInRange(kingCoords->x + 2, kingCoords->y - 1) &&
      board[kingCoords->y - 1][kingCoords->x + 2] == oposingKnight)
    return true;

  // Check for bishop and queen diagnol checks
  for (int i = 1; i < 8 - kingCoords->x; ++i) {
    if (!CE__isInRange(kingCoords->x + i, kingCoords->y + i))
      break;
    if (board[kingCoords->y + i][kingCoords->x + i] == oposingBishop ||
        board[kingCoords->y + i][kingCoords->x + i] == oposingQueen)
      return true;
    if (board[kingCoords->y + i][kingCoords->x + i] != CE_EMPTY)
      break;
  }

  for (int i = 1; i < 8 - kingCoords->x; ++i) {
    if (!CE__isInRange(kingCoords->x + i, kingCoords->y - i))
      break;
    if (board[kingCoords->y - i][kingCoords->x + i] == oposingBishop ||
        board[kingCoords->y - i][kingCoords->x + i] == oposingQueen)
      return true;
    if (board[kingCoords->y - i][kingCoords->x + i] != CE_EMPTY)
      break;
  }

  for (int i = 1; i < 8 - (8 - kingCoords->x); ++i) {
    if (!CE__isInRange(kingCoords->x - i, kingCoords->y - i))
      break;
    if (board[kingCoords->y - i][kingCoords->x - i] == oposingBishop ||
        board[kingCoords->y - i][kingCoords->x - i] == oposingQueen)
      return true;
    if (board[kingCoords->y - i][kingCoords->x - i] != CE_EMPTY)
      break;
  }

  for (int i = 1; i < 8 - (8 - kingCoords->x); ++i) {
    if (!CE__isInRange(kingCoords->x - i, kingCoords->y + i))
      break;
    if (board[kingCoords->y + i][kingCoords->x - i] == oposingBishop ||
        board[kingCoords->y + i][kingCoords->x - i] == oposingQueen)
      return true;
    if (board[kingCoords->y + i][kingCoords->x - i] != CE_EMPTY)
      break;
  }

  // King check
  // NOTE
  // It's impossible for a king check to occur, however it does have to be
  // checked due to kings needing to be unable to put the other in check
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      int x = kingCoords->x + i;
      int y = kingCoords->y + j;
      if (!CE__isInRange(kingCoords->x + i, kingCoords->y + j))
        continue;
      if (board[y][x] == oposingKing)
        return true;
    }
  }
  return false;
}

bool CE__isCurrPlayerCheck(CE_Game *game) {
  return CE__isCheck(game, game->currPlayer);
}

void CE__movePiece(CE_Game *game, CE_Coord *src, CE_Coord *dst) {
  printf("HELLO\n");
  printf("move: (%d, %d) -> (%d, %d)\n", src->x, src->y, dst->x, dst->y);
  CE__printBoard(game);
  printf("\n\n");
  if (src->x == dst->x && src->y == dst->y)
    return;
  CE_SquareTypes **board = game->board;

  board[dst->y][dst->x] = board[src->y][src->x];
  board[src->y][src->x] = CE_EMPTY;
  printf("dst: %d\n", board[dst->y][dst->x]);
  printf("src: %d\n", board[src->y][src->x]);
  CE__printBoard(game);
}

CE_Player CE__getPlayer(CE_SquareTypes *square) {
  switch (*square) {
  case CE_WHITE_PAWN:
  case CE_WHITE_KING:
  case CE_WHITE_ROOK:
  case CE_WHITE_QUEEN:
  case CE_WHITE_BISHOP:
  case CE_WHITE_KNIGHT:
    return CE_WHITE_PLAYER;
  case CE_BLACK_PAWN:
  case CE_BLACK_KING:
  case CE_BLACK_ROOK:
  case CE_BLACK_QUEEN:
  case CE_BLACK_BISHOP:
  case CE_BLACK_KNIGHT:
    return CE_BLACK_PLAYER;
  case CE_EMPTY:
  default:
    return CE_NO_PLAYER;
  }
}

// Returns a copy of the board where the square has moved
CE_Game *CE__cpMovePiece(CE_Game *game, CE_Coord *dst, CE_Coord *src) {
  CE_Game *cpyGame = CE_initGame();
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      cpyGame->board[i][j] = game->board[i][j];
    }
  }
  CE__movePiece(cpyGame, dst, src);
  return cpyGame;
}

// Function to see if can make default move, AKA direct capture or empty square
bool CE__canMoveTo(CE_Game *game, CE_Coord *pieceToMove, CE_Coord *moveTo,
                   CE_Coord **validMovesArr, size_t *validMovesSize) {

  bool inRange = CE__isInRange(moveTo->x, moveTo->y);

  if (!inRange)
    return false;

  bool isSamePlayer =
      CE__getPlayer(&game->board[moveTo->y][moveTo->x]) ==
      CE__getPlayer(&game->board[pieceToMove->y][pieceToMove->x]);

  if (isSamePlayer)
    return false;

  bool isCheckAfterMove =
      CE__isCheck(CE__cpMovePiece(game, pieceToMove, moveTo),
                  CE__getPlayer(&game->board[pieceToMove->y][pieceToMove->x]));

  if (isCheckAfterMove)
    return false;

  validMovesArr[*validMovesSize] = (CE_Coord *)malloc(sizeof(CE_Coord));
  validMovesArr[*validMovesSize]->y = moveTo->y;
  validMovesArr[*validMovesSize]->x = moveTo->x;
  ++*validMovesSize;
  return game->board[moveTo->y][moveTo->x] == CE_EMPTY;
}