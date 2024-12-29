#include "engine.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool isInRange(int y, int x) { return y >= 0 && y < 8 && x >= 0 && x < 8; }

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

void printBoard(Game *game) {
  SquareTypes **board = game->board;
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

bool isCheck(Game *game, Player player) {
  SquareTypes **board = game->board;
  SquareTypes king = player == WHITE ? WHITE_KING : BLACK_KING;
  SquareTypes oposingRook = player == WHITE ? BLACK_ROOK : WHITE_ROOK;
  SquareTypes oposingQueen = player == WHITE ? BLACK_QUEEN : WHITE_QUEEN;
  SquareTypes oposingBishop = player == WHITE ? BLACK_BISHOP : WHITE_BISHOP;
  SquareTypes oposingPawn = player == WHITE ? BLACK_PAWN : WHITE_PAWN;
  SquareTypes oposingKnight = player == WHITE ? BLACK_KNIGHT : WHITE_KNIGHT;
  SquareTypes oposingKing = player == WHITE ? BLACK_KING : WHITE_KING;

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
    printBoard(game);
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
  if ((isInRange(kingCoords->x + 1, kingCoords->y + moveIncrement) &&
       board[kingCoords->y + moveIncrement][kingCoords->x + 1] ==
           oposingPawn) ||
      (isInRange(kingCoords->x - 1, kingCoords->y + moveIncrement) &&
       board[kingCoords->y + moveIncrement][kingCoords->x - 1] == oposingPawn))
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

  // King check
  // NOTE
  // It's impossible for a king check to occur, however it does have to be
  // checked due to kings needing to be unable to put the other in check
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      int x = kingCoords->x + i;
      int y = kingCoords->y + j;
      if (!isInRange(kingCoords->x + i, kingCoords->y + j))
        continue;
      if (board[y][x] == oposingKing)
        return true;
    }
  }
  return false;
}

bool isCurrPlayerCheck(Game *game) { return isCheck(game, game->currPlayer); }

void movePiece(SquareTypes **board, Coord *src, Coord *dst) {
  if (src->x == dst->x && src->y == dst->y)
    return;
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
  case EMPTY:
    return NONE;
  }
}

// Returns a copy of the board where the square has moved
Game *cpMovePiece(Game *game, Coord *dst, Coord *src) {
  Game *cpyGame = initGame();
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      cpyGame->board[i][j] = game->board[i][j];
    }
  }
  movePiece(cpyGame->board, dst, src);
  return cpyGame;
}
// Function to see if can make default move, AKA direct capture or empty square
bool canMoveTo(Game *game, Coord *pieceToMove, Coord *moveTo,
               Coord **validMovesArr, size_t *validMovesSize) {

  bool inRange = isInRange(moveTo->x, moveTo->y);

  printf("Is in range: %d\n", inRange);
  if (!inRange)
    return false;

  bool isSamePlayer = getPlayer(&game->board[moveTo->y][moveTo->x]) ==
                      getPlayer(&game->board[pieceToMove->y][pieceToMove->x]);

  printf("Is same player: %d\n", isSamePlayer);
  if (isSamePlayer)
    return false;

  bool isCheckAfterMove =
      isCheck(cpMovePiece(game, pieceToMove, moveTo),
              getPlayer(&game->board[pieceToMove->y][pieceToMove->x]));
  printf("Is check after move: %d\n", isCheckAfterMove);

  if (isCheckAfterMove)
    return false;

  printf("Can move to: (%d, %d)\n", moveTo->x, moveTo->y);
  validMovesArr[*validMovesSize] = (Coord *)malloc(sizeof(Coord));
  validMovesArr[*validMovesSize]->y = moveTo->y;
  validMovesArr[*validMovesSize]->x = moveTo->x;
  ++*validMovesSize;
  return game->board[moveTo->y][moveTo->x] == EMPTY;
}

// TODO: add the rest of the pieces, but before that I need a move and ischeck
// function to check if the move is valid or if the player is then in check

Coord **getValidMoves(Game *game, Coord *pieceToMove, size_t *returnSize) {
  SquareTypes **board = game->board;
  Coord **validMoves = malloc(100 * sizeof(Coord *)); // Adjust size as needed
  size_t validMovesIndex = 0;
  int yOrigin = pieceToMove->y;
  int xOrigin = pieceToMove->x;
  printf("Origin: (%d, %d)\n", xOrigin, yOrigin);

  // This will be used to check if a piece on a square is on the same team as
  // the piece to move if not, you can capture
  Player currPlayer = getPlayer(&board[pieceToMove->y][pieceToMove->x]);

  if (currPlayer == NONE) {
    printf("Invalid square\n");
    printf("Square: %d\n", currPlayer);
    return validMoves;
  }

  Player oppPlayer = currPlayer == WHITE ? BLACK : WHITE;
  int pawnIncrement = currPlayer == WHITE ? 1 : -1;
  printf("yOrigin: %d, xOrigin: %d\n", yOrigin, xOrigin);
  printf("%d\n", board[yOrigin][xOrigin]);
  printBoard(game);
  switch (board[yOrigin][xOrigin]) {
  case WHITE_PAWN:
  case BLACK_PAWN:
    printf("Is pawn\n");

    if (board[yOrigin + pawnIncrement][xOrigin] == EMPTY &&
        !isCheck(cpMovePiece(game, pieceToMove,
                             &(Coord){xOrigin, yOrigin + pawnIncrement}),
                 currPlayer)) {
      validMoves[validMovesIndex] = (Coord *)malloc(sizeof(Coord));
      validMoves[validMovesIndex]->y = yOrigin + pawnIncrement;
      validMoves[validMovesIndex]->x = xOrigin;
      ++validMovesIndex;
    }

    bool canEnPassant1 = game->enPassantSquare != NULL &&
                         xOrigin + 1 == game->enPassantSquare->x &&
                         yOrigin + pawnIncrement == game->enPassantSquare->y;
    bool canCapture1 =
        getPlayer(&game->board[yOrigin + pawnIncrement][xOrigin + 1]) ==
        oppPlayer;

    if (isInRange(xOrigin + 1, yOrigin + pawnIncrement) &&
        (canCapture1 || canEnPassant1) &&
        !isCheck(cpMovePiece(game, pieceToMove,
                             &(Coord){xOrigin + 1, yOrigin + pawnIncrement}),
                 getPlayer(&game->board[pieceToMove->y][pieceToMove->x]))) {
      validMoves[validMovesIndex] = (Coord *)malloc(sizeof(Coord));
      validMoves[validMovesIndex]->y = yOrigin + pawnIncrement;
      validMoves[validMovesIndex]->x = xOrigin + 1;
      ++validMovesIndex;
    }

    bool canEnPassant2 = xOrigin - 1 == game->enPassantSquare->x &&
                         yOrigin + pawnIncrement == game->enPassantSquare->y;
    bool canCapture2 =
        getPlayer(&game->board[yOrigin + pawnIncrement][xOrigin - 1]) ==
        oppPlayer;

    if (isInRange(xOrigin - 1, yOrigin + pawnIncrement) &&
        (canEnPassant2 || canCapture2) &&
        !isCheck(cpMovePiece(game, pieceToMove,
                             &(Coord){xOrigin - 1, yOrigin + pawnIncrement}),
                 getPlayer(&game->board[pieceToMove->y][pieceToMove->x]))) {
      validMoves[validMovesIndex] = (Coord *)malloc(sizeof(Coord));
      validMoves[validMovesIndex]->y = yOrigin + pawnIncrement;
      validMoves[validMovesIndex]->x = xOrigin - 1;
      ++validMovesIndex;
    }

    if (isInRange(xOrigin, yOrigin + pawnIncrement * 2) &&
        game->board[yOrigin + pawnIncrement * 2][xOrigin] == EMPTY &&
        yOrigin == (currPlayer == WHITE ? 1 : 6)) {

      validMoves[validMovesIndex] = (Coord *)malloc(sizeof(Coord));
      validMoves[validMovesIndex]->y = yOrigin + pawnIncrement * 2;
      validMoves[validMovesIndex]->x = xOrigin;
      ++validMovesIndex;
    }

    break;

  case WHITE_ROOK:
  case BLACK_ROOK:
    printf("Is rook\n");
    for (int x = pieceToMove->x - 1; x >= 0; --x) {
      if (!canMoveTo(game, pieceToMove, &(Coord){x, yOrigin}, validMoves,
                     &validMovesIndex))
        break;
    }

    for (int x = pieceToMove->x + 1; x < 8; ++x) {
      if (!canMoveTo(game, pieceToMove, &(Coord){x, yOrigin}, validMoves,
                     &validMovesIndex))
        break;
    }

    for (int y = pieceToMove->y - 1; y >= 0; --y) {
      if (!canMoveTo(game, pieceToMove, &(Coord){xOrigin, y}, validMoves,
                     &validMovesIndex))
        break;
    }

    for (int y = pieceToMove->y + 1; y < 8; ++y) {
      if (!canMoveTo(game, pieceToMove, &(Coord){xOrigin, y}, validMoves,
                     &validMovesIndex))
        break;
    }
    break;

  case WHITE_BISHOP:
  case BLACK_BISHOP:
    printf("is bishop\n");
    for (int i = 1; i < 7 - xOrigin; ++i) {
      if (!canMoveTo(game, pieceToMove, &(Coord){xOrigin + i, yOrigin + i},
                     validMoves, &validMovesIndex))
        break;
    }

    for (int i = 1; i < 7 - xOrigin; ++i) {
      if (!canMoveTo(game, pieceToMove, &(Coord){xOrigin + i, yOrigin - i},
                     validMoves, &validMovesIndex))
        break;
    }

    for (int i = 1; i < xOrigin; ++i) {
      if (!canMoveTo(game, pieceToMove, &(Coord){xOrigin - i, yOrigin - i},
                     validMoves, &validMovesIndex))
        break;
    }

    for (int i = 1; i < xOrigin; ++i) {
      if (!canMoveTo(game, pieceToMove, &(Coord){xOrigin - i, yOrigin + i},
                     validMoves, &validMovesIndex))
        break;
    }

    break;
  case WHITE_KING:
  case BLACK_KING:
    printf("Is king\n");
    for (int i = -1; i <= 1; ++i) {
      for (int j = -1; j <= 1; ++j) {
        int x = xOrigin + i;
        int y = yOrigin + j;
        printf("Coords: (%d, %d)\n", x, y);
        canMoveTo(game, pieceToMove, &(Coord){x, y}, validMoves,
                  &validMovesIndex);
      }
    }
    bool hasCastlingRights = currPlayer == WHITE ? game->whiteHasCastleRight
                                                 : game->blackHasCastleRight;
    printf("Has castling rights: %d\n", hasCastlingRights);
    if (!hasCastlingRights)
      break;

    SquareTypes playerRook = currPlayer == WHITE ? WHITE_ROOK : BLACK_ROOK;

    bool canReachRook1 = game->board[yOrigin][xOrigin + 1] == EMPTY &&
                         game->board[yOrigin][xOrigin + 2] == EMPTY;
    bool isInCheck1 =
        isCheck(cpMovePiece(game, pieceToMove, &(Coord){xOrigin + 1, yOrigin}),
                currPlayer) &&
        isCheck(cpMovePiece(game, pieceToMove, &(Coord){xOrigin + 2, yOrigin}),
                currPlayer);
    bool isRookAvailable1 = game->board[yOrigin][xOrigin + 3] == playerRook;

    printf("canReachRook == %d, isInCheck == %d, isRookAvailable == %d\n", canReachRook1, isInCheck1, isRookAvailable1);
    if (canReachRook1 && !isInCheck1 && isRookAvailable1) {
      validMoves[validMovesIndex] = (Coord *)malloc(sizeof(Coord));
      validMoves[validMovesIndex]->x = xOrigin + 2;
      validMoves[validMovesIndex]->y = yOrigin;
      ++validMovesIndex;
    }

    bool canReachRook2 = game->board[yOrigin][xOrigin - 1] == EMPTY &&
                         game->board[yOrigin][xOrigin - 2] == EMPTY &&
                         game->board[yOrigin][xOrigin - 3] == EMPTY;
    bool isInCheck2 =
        isCheck(cpMovePiece(game, pieceToMove, &(Coord){xOrigin + 1, yOrigin}),
                currPlayer) &&
        isCheck(cpMovePiece(game, pieceToMove, &(Coord){xOrigin + 2, yOrigin}),
                currPlayer);
    bool isRookAvailable2 = game->board[yOrigin][xOrigin - 4] == playerRook;

    printf("canReachRook == %d, isInCheck == %d, isRookAvailable == %d\n", canReachRook2, isInCheck2, isRookAvailable2);
    if (canReachRook2 && !isInCheck2 && isRookAvailable2) {
      validMoves[validMovesIndex] = (Coord *)malloc(sizeof(Coord));
      validMoves[validMovesIndex]->x = xOrigin - 2;
      validMoves[validMovesIndex]->y = yOrigin;
      ++validMovesIndex;
    }

    break;
  case WHITE_KNIGHT:
  case BLACK_KNIGHT:
    printf("Is knight\n");
    canMoveTo(game, pieceToMove, &(Coord){xOrigin + 2, yOrigin + 1}, validMoves,
              &validMovesIndex);
    canMoveTo(game, pieceToMove, &(Coord){xOrigin + 2, yOrigin - 1}, validMoves,
              &validMovesIndex);
    canMoveTo(game, pieceToMove, &(Coord){xOrigin - 2, yOrigin + 1}, validMoves,
              &validMovesIndex);
    canMoveTo(game, pieceToMove, &(Coord){xOrigin - 2, yOrigin - 1}, validMoves,
              &validMovesIndex);
    canMoveTo(game, pieceToMove, &(Coord){xOrigin + 1, yOrigin + 2}, validMoves,
              &validMovesIndex);
    canMoveTo(game, pieceToMove, &(Coord){xOrigin + 1, yOrigin - 2}, validMoves,
              &validMovesIndex);
    canMoveTo(game, pieceToMove, &(Coord){xOrigin - 1, yOrigin + 2}, validMoves,
              &validMovesIndex);
    canMoveTo(game, pieceToMove, &(Coord){xOrigin - 1, yOrigin - 2}, validMoves,
              &validMovesIndex);
    break;
  case WHITE_QUEEN:
  case BLACK_QUEEN:

    printf("Is queen\n");
    for (int i = 1; i < 7 - xOrigin; ++i) {
      if (!canMoveTo(game, pieceToMove, &(Coord){xOrigin + i, yOrigin + i},
                     validMoves, &validMovesIndex))
        break;
    }

    for (int i = 1; i < 7 - xOrigin; ++i) {
      if (!canMoveTo(game, pieceToMove, &(Coord){xOrigin + i, yOrigin - i},
                     validMoves, &validMovesIndex))
        break;
    }

    for (int i = 1; i < xOrigin; ++i) {
      if (!canMoveTo(game, pieceToMove, &(Coord){xOrigin - i, yOrigin - i},
                     validMoves, &validMovesIndex))
        break;
    }

    for (int i = 1; i < xOrigin; ++i) {
      if (!canMoveTo(game, pieceToMove, &(Coord){xOrigin - i, yOrigin + i},
                     validMoves, &validMovesIndex))
        break;
    }

    for (int x = pieceToMove->x - 1; x >= 0; --x) {
      if (!canMoveTo(game, pieceToMove, &(Coord){x, yOrigin}, validMoves,
                     &validMovesIndex))
        break;
    }

    for (int x = pieceToMove->x + 1; x < 8; ++x) {
      if (!canMoveTo(game, pieceToMove, &(Coord){x, yOrigin}, validMoves,
                     &validMovesIndex))
        break;
    }

    for (int y = pieceToMove->y - 1; y >= 0; --y) {
      if (!canMoveTo(game, pieceToMove, &(Coord){xOrigin, y}, validMoves,
                     &validMovesIndex))
        break;
    }

    for (int y = pieceToMove->y + 1; y < 8; ++y) {
      if (!canMoveTo(game, pieceToMove, &(Coord){xOrigin, y}, validMoves,
                     &validMovesIndex))
        break;
    }

    break;
  default:
    printf("What??\n");
  }
  *returnSize = validMovesIndex;
  return validMoves;
}

Game *initGame() {
  Game *game = (Game *)malloc(sizeof(Game));
  game->board = createBoard();
  game->currPlayer = WHITE;
  game->whiteHasCastleRight = true;
  game->blackHasCastleRight = true;
  game->enPassantSquare = (Coord *)malloc(sizeof(Coord));
  game->enPassantSquare->y = -1;
  game->enPassantSquare->x = -1;
  return game;
}
