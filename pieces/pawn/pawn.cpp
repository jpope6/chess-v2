#include "pawn.h"

// Constructor
Pawn::Pawn(int row, int col, char name, bool is_white)
    : Piece(row, col, name, is_white) {
  this->has_moved = false;
}

// TODO: FIX THIS
// void Pawn::updateLegalMoves() {
//   this->setPotentialMoves({{1, 0}});
//
//   if (!this->getHasMoved()) {
//     this->getPotentialMoves().push_back({2, 0});
//   }
// }