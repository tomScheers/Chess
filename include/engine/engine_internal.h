#ifndef ENGINE_INTERNAL_H
#define ENGINE_INTERNAL_H
#include "engine.h"
#include <stdbool.h>
#include <stdlib.h>

CE_SquareTypes **CE__createBoard();
void CE__printBoard(CE_Game *game);
void CE__movePiece(CE_Game *game, CE_Coord *src, CE_Coord *dst);
bool CE__isCheck(CE_Game *game, CE_Player player);
bool CE__isCurrPlayerCheck(CE_Game *game);
bool CE__isInRange(int y, int x);
bool CE__canMoveTo(CE_Game *game, CE_Coord *pieceToMove, CE_Coord *moveTo,
                   CE_Coord **validMovesArr, size_t *validMovesSize);
CE_Player CE__getPlayer(CE_SquareTypes *square);
CE_Game *CE__cpMovePiece(CE_Game *game, CE_Coord *dst, CE_Coord *src);

#endif