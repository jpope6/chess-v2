#ifndef FRAME_H
#define FRAME_H

#include <wx/bitmap.h>
#include <wx/dialog.h>
#include <wx/image.h>
#include <wx/timer.h>
#include <wx/wx.h>

#include <map>
#include <string>
#include <utility>

#include "../bot/bot.h"

using namespace std;

class Frame : public wxFrame {
private:
  map<char, wxBitmap> chessPieceBitmaps;
  Bot bot;
  Board chessboard;

  wxDialog *promotionDialog;

  int mouse_x;
  int mouse_y;

  bool is_piece_selected;
  Piece *selected_piece;
  int selected_piece_square;

  wxTimer *timer;
  bool bot_move_made;

public:
  // Constructor
  Frame();

  // Member functions
  void loadChessPieces();
  void createPromotionDialog(wxDialog *dialog);

  // Drawing functions
  void onPaint(wxPaintEvent &event);
  void drawSquares(wxPaintDC &dc, int row, int col, wxCoord square_size);
  void drawInactivePiece(wxPaintDC &dc, int row, int col, wxCoord square_size);
  void drawActivePiece(wxPaintDC &dc);

  // Mouse events
  void onMouseLeftDown(wxMouseEvent &event);
  void onMouseLeftUp(wxMouseEvent &event);
  void onMouseMotion(wxMouseEvent &event);

  // Timer event
  void onTimer(wxTimerEvent &event);

  // Exit
  void onPromotionDialogClose(wxCloseEvent &event);
  void onExit(wxCommandEvent &event);

  DECLARE_EVENT_TABLE()
};

#endif
