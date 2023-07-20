#include "piece.h"

Piece::Piece(int square, char piece) {
  this->row = square / 8;
  this->col = square % 8;
  this->square = square;
  this->name = piece;
  this->color = isupper(piece) ? WHITE : BLACK;

  piece = toupper(piece);
  map<char, Type> piece_type_map = {{'P', PAWN}, {'N', KNIGHT}, {'B', BISHOP},
                                    {'R', ROOK}, {'Q', QUEEN},  {'K', KING}};
  this->piece_type = piece_type_map[piece];

  this->has_moved = false;
}