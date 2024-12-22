#include "engine.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

SquareTypes **createBoard() {
  SquareTypes **board = (SquareTypes **)malloc(sizeof(SquareTypes *) * 8);
  for (int i = 0; i < 8; ++i) {
    board[i] = (SquareTypes *)malloc(sizeof(SquareTypes) * 8);
  }
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
  board[7][2] = BLACK_BISHOP;
  board[7][3] = BLACK_QUEEN;
  board[7][4] = BLACK_KING;
  board[7][5] = BLACK_BISHOP;
  board[7][6] = BLACK_KNIGHT;
  board[7][7] = BLACK_ROOK;
  for (int i = 0; i < 8; ++i) {
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
      switch (board[i][j]) {
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

bool isCheck(SquareTypes **board, Player player) {
  SquareTypes king = player == WHITE ? WHITE_KING : BLACK_KING;
  SquareTypes oposingRook = player == WHITE ? BLACK_ROOK : WHITE_ROOK;
  SquareTypes oposingQueen = player == WHITE ? BLACK_QUEEN : WHITE_QUEEN;
  SquareTypes oposingBishop = player == WHITE ? BLACK_BISHOP : WHITE_BISHOP;
  SquareTypes oposingPawn = player == WHITE ? BLACK_PAWN : WHITE_PAWN;
  SquareTypes oposingKnight = player == WHITE ? BLACK_KNIGHT : WHITE_KNIGHT;

  // Black's pawns move 'downwards' from the arrays perspective, so the program
  // needs to take that into acount
  int moveIncrement = player == WHITE ? 1 : -1;

  Coord *kingCoords = (Coord *)malloc(sizeof(Coord));
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
    fprintf(stderr, "No kingcoords\n");
    exit(EXIT_FAILURE);
  }

  // Check for horizontal queen and rook checks
  // Check from right-hand side
  for (int x = kingCoords->x + 1; x < 8; ++x) {
    if (board[kingCoords->y][x] == oposingRook ||
        board[kingCoords->y][x] == oposingQueen)
      return true;
    if (board[kingCoords->y][x] != EMPTY)
      break;
  }
  // Check from left-hand side
  for (int x = kingCoords->x - 1; x >= 0; --x) {
    if (board[kingCoords->y][x] == oposingRook ||
        board[kingCoords->y][x] == oposingQueen)
      return true;
    if (board[kingCoords->y][x] != EMPTY)
      break;
  }

  // Check for vertical queen and rook checks
  // Check from right-hand side
  for (int y = kingCoords->y - 1; y >= 0; --y) {
    if (board[y][kingCoords->x] == oposingRook ||
        board[y][kingCoords->x] == oposingQueen)
      return true;
    if (board[y][kingCoords->x] != EMPTY)
      break;
  }
  // Check from left-hand side
  for (int y = kingCoords->y + 1; y < 8; ++y) {
    if (board[y][kingCoords->x] == oposingRook ||
        board[y][kingCoords->x] == oposingQueen)
      return true;
    if (board[y][kingCoords->x] != EMPTY)
      break;
  }

  // Check pawn checks
  if ((isInRange(kingCoords->x + 1, kingCoords->y + moveIncrement) && board[kingCoords->y + moveIncrement][kingCoords->x + 1] == oposingPawn) ||
      (isInRange(kingCoords->x - 1, kingCoords->y + moveIncrement) && board[kingCoords->y + moveIncrement][kingCoords->x - 1] == oposingPawn))
    return true;

  // Check for knight checks
  if (isInRange(kingCoords->x + 1, kingCoords->y + 2) &&
      board[kingCoords->y + 2][kingCoords->x + 1] == oposingKnight)
    return true;

  if (isInRange(kingCoords->x - 1, kingCoords->y + 2) &&
      board[kingCoords->y + 2][kingCoords->x - 1] == oposingKnight)
    return true;

  if (isInRange(kingCoords->x - 2, kingCoords->y + 1) &&
      board[kingCoords->y + 1][kingCoords->x - 2] == oposingKnight)
    return true;

  if (isInRange(kingCoords->x - 2, kingCoords->y - 1) &&
      board[kingCoords->y - 1][kingCoords->x - 2] == oposingKnight)
    return true;

  if (isInRange(kingCoords->x + 1, kingCoords->y - 2) &&
      board[kingCoords->y - 2][kingCoords->x + 1] == oposingKnight)
    return true;

  if (isInRange(kingCoords->x - 1, kingCoords->y - 2) &&
      board[kingCoords->y - 2][kingCoords->x - 1] == oposingKnight)
    return true;

  if (isInRange(kingCoords->x + 2, kingCoords->y + 1) &&
      board[kingCoords->y + 1][kingCoords->x + 2] == oposingKnight)
    return true;

  if (isInRange(kingCoords->x + 2, kingCoords->y - 1) &&
      board[kingCoords->y - 1][kingCoords->x + 2] == oposingKnight)
    return true;

  // Check for bishop and queen diagnol checks
  for (int i = 1; i < 8 - kingCoords->x; ++i) {
    if (!isInRange(kingCoords->x + i, kingCoords->y + i))
      break;
    if (board[kingCoords->y + i][kingCoords->x + i] == oposingBishop ||
        board[kingCoords->y + i][kingCoords->x + i] == oposingQueen)
      return true;
    if (board[kingCoords->y + i][kingCoords->x + i] != EMPTY)
      break;
  }

  for (int i = 1; i < 8 - kingCoords->x; ++i) {
    if (!isInRange(kingCoords->x + i, kingCoords->y - i))
      break;
    if (board[kingCoords->y - i][kingCoords->x + i] == oposingBishop ||
        board[kingCoords->y - i][kingCoords->x + i] == oposingQueen)
      return true;
    if (board[kingCoords->y - i][kingCoords->x + i] != EMPTY)
      break;
  }

  for (int i = 1; i < 8 - (8 - kingCoords->x); ++i) {
    if (!isInRange(kingCoords->x - i, kingCoords->y - i))
      break;
    if (board[kingCoords->y - i][kingCoords->x - i] == oposingBishop ||
        board[kingCoords->y - i][kingCoords->x - i] == oposingQueen)
      return true;
    if (board[kingCoords->y - i][kingCoords->x - i] != EMPTY)
      break;
  }

  for (int i = 1; i < 8 - (8 - kingCoords->x); ++i) {
    if (!isInRange(kingCoords->x - i, kingCoords->y + i))
      break;
    if (board[kingCoords->y + i][kingCoords->x - i] == oposingBishop ||
        board[kingCoords->y + i][kingCoords->x - i] == oposingQueen)
      return true;
    if (board[kingCoords->y + i][kingCoords->x - i] != EMPTY)
      break;
  }
  return false;
}

void movePiece(SquareTypes **board, Coord *src, Coord *dst) {
  if (src->x == dst->x && src->y == dst->y) return;
  board[dst->y][dst->x] = board[src->y][src->x];
  board[src->y][src->x] = EMPTY;
}

Player getPlayer(SquareTypes *square) {
  switch (*square) {
  case WHITE_PAWN:
  case WHITE_KING:
  case WHITE_ROOK:
  case WHITE_QUEEN:
  case WHITE_BISHOP:
  case WHITE_KNIGHT:
    return WHITE;
  case BLACK_PAWN:
  case BLACK_KING:
  case BLACK_ROOK:
  case BLACK_QUEEN:
  case BLACK_BISHOP:
  case BLACK_KNIGHT:
    return BLACK;
  default:
    return NONE;
  }
}

bool isInRange(int y, int x) { return y >= 0 && y < 8 && x >= 0 && x < 8; }

// TODO: add the rest of the pieces, but before that I need a move and ischeck
// function to check if the move is valid or if the player is then in check

Coord **getValidMoves(SquareTypes **board, Coord *pieceToMove,
                      size_t *returnSize) {
  Coord **validMoves = malloc(100 * sizeof(Coord *)); // Adjust size as needed
  size_t validMovesIndex = 0;
  int yOrigin = pieceToMove->y;
  int xOrigin = pieceToMove->x;
  // This will be used to check if a piece on a square is on the same team as
  // the piece to move if not, you can capture
  Player currPlayer = getPlayer(&board[pieceToMove->y][pieceToMove->x]);
  int pawnIncrement = currPlayer == WHITE ? 1 : -1;
  printf("%d\n", board[pieceToMove->y][pieceToMove->x]);
  switch (board[pieceToMove->y][pieceToMove->x]) {
  case WHITE_PAWN:
  case BLACK_PAWN:
    printf("Is white pawn\n");
    if (board[pieceToMove->y + 1][pieceToMove->x] == EMPTY) {
      validMoves[validMovesIndex] = (Coord *)malloc(sizeof(Coord));
      validMoves[validMovesIndex]->y = yOrigin + pawnIncrement;
      validMoves[validMovesIndex]->x = xOrigin;
      ++validMovesIndex;
    }
    if (currPlayer !=
        getPlayer(&board[pieceToMove->y + 1][pieceToMove->x + 1])) {
      validMoves[validMovesIndex] = malloc(sizeof(Coord));
      validMoves[validMovesIndex]->y = yOrigin + pawnIncrement;
      validMoves[validMovesIndex]->x = xOrigin + 1;
      ++validMovesIndex;
    }
    if (currPlayer !=
        getPlayer(&board[pieceToMove->y + 1][pieceToMove->x - 1])) {
      validMoves[validMovesIndex] = malloc(sizeof(Coord));
      validMoves[validMovesIndex]->y = yOrigin + pawnIncrement;
      validMoves[validMovesIndex]->x = xOrigin - 1;
      ++validMovesIndex;
    }
    break;

  case WHITE_ROOK:
  case BLACK_ROOK:
    for (int x = pieceToMove->x; x >= 0; --x) {
      if (board[yOrigin][x] != EMPTY &&
          currPlayer == getPlayer(&board[yOrigin][x]))
        break;

      validMoves[validMovesIndex] = malloc(sizeof(Coord));
      validMoves[validMovesIndex]->y = yOrigin;
      validMoves[validMovesIndex]->x = x;
      ++validMovesIndex;
    }

    for (int x = pieceToMove->x; x < 8; ++x) {
      if (board[yOrigin][x] != EMPTY &&
          currPlayer == getPlayer(&board[yOrigin][x]))
        break;

      validMoves[validMovesIndex] = malloc(sizeof(Coord));
      validMoves[validMovesIndex]->y = yOrigin;
      validMoves[validMovesIndex]->x = x;
      ++validMovesIndex;
    }

    for (int y = pieceToMove->y; y >= 0; --y) {
      if (board[y][xOrigin] != EMPTY &&
          currPlayer == getPlayer(&board[y][xOrigin]))
        break;

      validMoves[validMovesIndex] = malloc(sizeof(Coord));
      validMoves[validMovesIndex]->y = y;
      validMoves[validMovesIndex]->x = xOrigin;
      ++validMovesIndex;
    }

    for (int y = pieceToMove->y; y >= 0; --y) {
      if (board[y][xOrigin] != EMPTY &&
          currPlayer == getPlayer(&board[y][xOrigin]))
        break;

      validMoves[validMovesIndex] = malloc(sizeof(Coord));
      validMoves[validMovesIndex]->y = y;
      validMoves[validMovesIndex]->x = xOrigin;
      ++validMovesIndex;
    }
    break;

  case WHITE_KING:
  case BLACK_KING:
    printf("HELLO\n");
    for (int i = -1; i <= 1; ++i) {
      for (int j = -1; j <= 1; ++j) {
        if (isInRange(xOrigin + i, yOrigin + j) &&
            currPlayer != getPlayer(&board[yOrigin + i][xOrigin + j])) {
          validMoves[validMovesIndex] = malloc(sizeof(Coord));
          validMoves[validMovesIndex]->y = yOrigin + i;
          validMoves[validMovesIndex]->x = xOrigin + j;
          ++validMovesIndex;
        }
      }
    }
    break;
  case WHITE_KNIGHT:
  case BLACK_KNIGHT:
    printf("Knight\n");
    for (int i = 1; i <= 2; ++i) {
      for (int j = 1; j <= 2; ++j) {
        if (isInRange(xOrigin + i, yOrigin + j) &&
            currPlayer != getPlayer(&board[yOrigin + j][xOrigin + i])) {
          validMoves[validMovesIndex] = malloc(sizeof(Coord));
          validMoves[validMovesIndex]->y = yOrigin + j;
          validMoves[validMovesIndex]->x = xOrigin + i;
          ++validMovesIndex;
        }

        if (isInRange(xOrigin + j, yOrigin + i) &&
            currPlayer != getPlayer(&board[yOrigin + i][xOrigin + j])) {
          validMoves[validMovesIndex] = malloc(sizeof(Coord));
          validMoves[validMovesIndex]->y = yOrigin + i;
          validMoves[validMovesIndex]->x = xOrigin + j;
          ++validMovesIndex;
        }
      }
      break;
    }
    if (isInRange(xOrigin + 2, yOrigin + 1) &&
        currPlayer != getPlayer(&board[yOrigin + 1][xOrigin + 2])) {
      validMoves[validMovesIndex] = malloc(sizeof(Coord));
      validMoves[validMovesIndex]->y = yOrigin + 1;
      validMoves[validMovesIndex]->x = xOrigin + 2;
      ++validMovesIndex;
    }
    break;
  default:
    printf("What??\n");
  }
  *returnSize = validMovesIndex; // Note: returnSize is now a pointer
  return validMoves;
}

// int main() {
//   SquareTypes **board = createBoard();
//   printf("Created board\n");
//   printBoard(board);
//   printf("Finished\n");
//   printf("\n\n\n");
//   Coord src = {0, 4};
//   Coord dst = {2, 4};
//   movePiece(board, &src, &dst);
//   printBoard(board);
//   size_t ret = 0;
//   Coord **coord = getValidMoves(board, &dst, &ret);
//   printf("Valid King Moves:\n");
//   for (int i = 0; i < ret; ++i) {
//     printf("(%d, %d)\n", coord[i]->x, coord[i]->y);
//   }
//   return EXIT_SUCCESS;
// }
