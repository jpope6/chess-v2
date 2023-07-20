#ifndef FRAME_H
#define FRAME_H

#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/wx.h>

#include <map>
#include <string>

#include "../board/board.h"

using namespace std;

class Frame : public wxFrame {
 private:
  map<char, wxBitmap> chessPieceBitmaps;
  Board chessboard;

  int mouse_x;
  int mouse_y;

  bool is_piece_selected;
  int selected_piece_square;

 public:
  // Constructor
  Frame();

  // Member functions
  void loadChessPieces();

  // Drawing functions
  void onPaint(wxPaintEvent &event);
  void drawSquares(wxPaintDC &dc, int row, int col, wxCoord square_size);
  void drawInactivePiece(wxPaintDC &dc, int row, int col, wxCoord square_size);
  void drawActivePiece(wxPaintDC &dc);

  // Mouse events
  void onMouseLeftDown(wxMouseEvent &event);
  void onMouseMotion(wxMouseEvent &event);

  // Exit
  void onExit(wxCommandEvent &event);

  DECLARE_EVENT_TABLE()
};

#endif