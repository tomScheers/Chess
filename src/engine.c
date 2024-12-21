#include "engine.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

SquareTypes **createBoard() {
  SquareTypes **board = (SquareTypes **)malloc(sizeof(SquareTypes *) * 8);
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
  board[7][2] = BLACK_BISHOP;
  board[7][3] = BLACK_KNIGHT;
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
  printf("Checking check\n");
  SquareTypes king = player == WHITE ? WHITE_KING : BLACK_KING;
  printf("Attacked king = %s\n", king == WHITE_KING ? "white" : "black");
  SquareTypes oposingRook = player == WHITE ? BLACK_ROOK : WHITE_ROOK;
  SquareTypes oposingQueen = player == WHITE ? BLACK_QUEEN : WHITE_QUEEN;
  SquareTypes oposingBishop = player == WHITE ? BLACK_BISHOP : WHITE_BISHOP;
  SquareTypes oposingPawn = player == WHITE ? BLACK_PAWN : WHITE_PAWN;
  SquareTypes oposingKnight = player == WHITE ? BLACK_KNIGHT : WHITE_KNIGHT;

  // Black's pawns move 'downwards' from the arrays perspective, so the program
  // needs to take that into acount
  int moveIncrement = player == WHITE ? 1 : -1;

  printf("Checking check\n");
  Coord *kingCoords = (Coord*)malloc(sizeof(Coord));
  kingCoords->y = -1;
  kingCoords->x = -1;
  for (int y = 0; y < 8; ++y) {
    for (int x = 0; x < 8; ++x) {
      printf("%d, %d\n", x, y);
      printf("%u == %u\n", board[y][x], king);
      if (board[y][x] == king) {
        printf("%d, %d\n", x, y);
        kingCoords->y = y;
        kingCoords->x = x;
        break;
      }
    }
    if (kingCoords->y != -1) break;
  }

  if (kingCoords->y == -1) {
    fprintf(stderr, "No kingcoords\n");
    exit(EXIT_FAILURE);
  }

  printf("%d, %d\n", kingCoords->x, kingCoords->y);
  printf("Checking check\n");
  // Check for horizontal queen and rook checks
  // Check from right-hand side
  for (int y = kingCoords->y; y < 8; ++y) {
    printf("%d, %d\n", y, kingCoords->x);
    if (board[y][kingCoords->x] == oposingRook ||
        board[y][kingCoords->x] == oposingQueen)
      return true;
    if (board[y][kingCoords->x] != EMPTY)
      break;
  }
  printf("Checking check\n");
  // Check from left-hand side
  for (int y = kingCoords->y; y >= 0; --y) {
    printf("%d, %d\n", y, kingCoords->x);
    if (board[y][kingCoords->x] == oposingRook ||
        board[y][kingCoords->x] == oposingQueen)
      return true;
    if (board[y][kingCoords->x] != EMPTY)
      break;
  }

  printf("Checking check\n");
  // Check for vertical queen and rook checks
  // Check from right-hand side
  for (int x = kingCoords->x; x >= 0; ++x) {
    if (board[kingCoords->y][x] == oposingRook ||
        board[kingCoords->y][x] == oposingQueen)
      return true;
    if (board[kingCoords->y][x] != EMPTY)
      break;
  }
  // Check from left-hand side
  for (int x = kingCoords->x; x >= 0; --x) {
    if (board[kingCoords->y][x] == oposingRook ||
        board[kingCoords->y][x] == oposingQueen)
      return true;
    if (board[kingCoords->y][x] != EMPTY)
      break;
  }

  printf("Checking check\n");
  // Check pawn checks
  if (board[kingCoords->y + moveIncrement][kingCoords->x + 1] == oposingPawn ||
      board[kingCoords->y + moveIncrement][kingCoords->x + 1] == oposingPawn)
    return true;

  // Check for knight checks
  if (kingCoords->y + 2 < 8 && kingCoords->x + 1 < 8 && board[kingCoords->y + 2][kingCoords->x + 1] == oposingKnight)
    return true;

  if (kingCoords->y + 2 < 8 && kingCoords->x - 1 < 8 && board[kingCoords->y + 2][kingCoords->x - 1] == oposingKnight)
    return true;

  if (kingCoords->y + 1 < 8 && kingCoords->x - 2 < 8 && board[kingCoords->y + 1][kingCoords->x - 2] == oposingKnight)
    return true;

  if (kingCoords->y - 1 < 8 && kingCoords->x - 2 < 8 && board[kingCoords->y - 1][kingCoords->x - 2] == oposingKnight)
    return true;

  if (kingCoords->y - 2 < 8 && kingCoords->x + 1 < 8 && board[kingCoords->y - 2][kingCoords->x + 1] == oposingKnight)
    return true;

  if (kingCoords->y - 2 < 8 && kingCoords->x - 1 < 8 && board[kingCoords->y - 2][kingCoords->x - 1] == oposingKnight)
    return true;

  if (kingCoords->y + 1 < 8 && kingCoords->x + 2 < 8 && board[kingCoords->y + 1][kingCoords->x + 2] == oposingKnight)
    return true;

  if (kingCoords->y - 1 < 8 && kingCoords->x + 2 < 8 && board[kingCoords->y - 1][kingCoords->x + 2] == oposingKnight)
    return true;

  printf("Checking check\n");
  // Check for bishop and queen diagnol checks
  for (int i = kingCoords->x; i < 8; ++i) {
    if (kingCoords->y + i >= 8 || kingCoords->x + i >= 8) break;
    if (board[kingCoords->y + i][kingCoords->x + i] == oposingBishop ||
        board[kingCoords->y + i][kingCoords->x + i] == oposingQueen)
      return true;
    if (board[kingCoords->y + i][kingCoords->x + i] != EMPTY)
      break;
  }

  for (int i = kingCoords->x; i < 8; ++i) {
    if (kingCoords->y + i >= 8 || kingCoords->x + i >= 8) break;
    if (board[kingCoords->y - i][kingCoords->x + i] == oposingBishop ||
        board[kingCoords->y - i][kingCoords->x + i] == oposingQueen)
      return true;
    if (board[kingCoords->y - i][kingCoords->x + i] != EMPTY)
      break;
  }

  for (int i = kingCoords->x; i >= 0; --i) {
    if (kingCoords->y + i >= 8 || kingCoords->x + i >= 8) break;
    if (board[kingCoords->y - i][kingCoords->x + i] == oposingBishop ||
        board[kingCoords->y - i][kingCoords->x + i] == oposingQueen)
      return true;
    if (board[kingCoords->y - i][kingCoords->x + i] != EMPTY)
      break;
  }

  for (int i = kingCoords->x; i >= 0; --i) {
    if (kingCoords->y + i >= 8 || kingCoords->x + i >= 8) break;
    if (board[kingCoords->y + i][kingCoords->x + i] == oposingBishop ||
        board[kingCoords->y + i][kingCoords->x + i] == oposingQueen)
      return true;
    if (board[kingCoords->y + i][kingCoords->x + i] != EMPTY)
      break;
  }
  return false;
}

void movePiece(SquareTypes **board, Coord *src, Coord *dst) {
  printf("%d\n", board[dst->y][dst->x]);
  board[dst->y][dst->x] = board[src->y][src->x];
  printf("%d\n", board[dst->y][dst->x]);
  board[src->y][src->x] = EMPTY;
}

// TODO: add the rest of the pieces, but before that I need a move and ischeck
// function to check if the move is valid or if the player is then in check

Coord **getValidMoves(SquareTypes **board, Coord *pieceToMove,
                      size_t *returnSize) {
  Coord **validMoves = malloc(100 * sizeof(Coord *)); // Adjust size as needed
  size_t validMovesIndex = 0;
  int yOrigin = pieceToMove->y;
  int xOrigin = pieceToMove->x;
  switch (board[pieceToMove->y][pieceToMove->x]) {
  case WHITE_PAWN:
    printf("Is white pawn\n");
    if (board[pieceToMove->y + 1][pieceToMove->x] == EMPTY) {
      validMoves[validMovesIndex] = (Coord *)malloc(sizeof(Coord));
      validMoves[validMovesIndex]->y = yOrigin + 1;
      validMoves[validMovesIndex]->x = xOrigin;
      validMovesIndex++;
    }
    if (board[pieceToMove->y + 1][pieceToMove->x + 1] != EMPTY) {
      validMoves[validMovesIndex] = malloc(sizeof(Coord));
      validMoves[validMovesIndex]->y = yOrigin + 1;
      validMoves[validMovesIndex]->x = xOrigin + 1;
      validMovesIndex++;
    }
    if (board[pieceToMove->y + 1][pieceToMove->x - 1] != EMPTY) {
      validMoves[validMovesIndex] = malloc(sizeof(Coord));
      validMoves[validMovesIndex]->y = yOrigin + 1;
      validMoves[validMovesIndex]->x = xOrigin - 1;
      validMovesIndex++;
    }
  }
  *returnSize = validMovesIndex; // Note: returnSize is now a pointer
  return validMoves;
}

int main() {
  SquareTypes **board = createBoard();
  printf("Created board\n");
  printBoard(board);
  printf("Finished\n");
  printf("\n\n\n");
  Coord src = {0, 1};
  Coord dst = {5, 3};
  printBoard(board);
  printf("is check: %b\n", isCheck(board, BLACK));
  return EXIT_SUCCESS;
}
