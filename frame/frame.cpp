#include "frame.h"

Frame::Frame()
    : wxFrame(nullptr, wxID_ANY, "Chess", wxDefaultPosition, wxSize(800, 837)) {
  chessboard = Board();
  loadChessPieces();

  mouse_x = 0;
  mouse_y = 0;

  is_piece_selected = false;
  selected_piece = nullptr;
  selected_piece_square = -1;

  Bind(wxEVT_PAINT, &Frame::onPaint, this);
  Bind(wxEVT_MENU, &Frame::onExit, this, wxID_EXIT);
}

// Load the chess piece images
void Frame::loadChessPieces() {
  char piece_names[] = {'b', 'k', 'n', 'p', 'q', 'r',
                        'B', 'K', 'N', 'P', 'Q', 'R'};

  for (char c : piece_names) {
    wxBitmap bitmap;

    // file path
    string path = "frame/images/" + string(1, c) + ".png";

    bool loadResult = bitmap.LoadFile(path, wxBITMAP_TYPE_PNG);

    // Scale the image to 100x100
    if (loadResult) {
      wxImage image = bitmap.ConvertToImage();
      image.Rescale(100, 100, wxIMAGE_QUALITY_HIGH);
      bitmap = wxBitmap(image);

      chessPieceBitmaps[c] = bitmap;
    }
  }
}

// Main drawing function
void Frame::onPaint(wxPaintEvent &event) {
  // Create a paint device
  wxPaintDC dc(this);

  wxSize size = GetClientSize();
  wxCoord square_size = size.GetWidth() / 8;

  // Draw the chess board
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      drawSquares(dc, row, col, square_size);
      drawInactivePiece(dc, row, col, square_size);
    }
  }

  // Draw the selected piece
  drawActivePiece(dc);
}

void Frame::drawSquares(wxPaintDC &dc, int row, int col, wxCoord square_size) {
  wxCoord x = col * square_size;
  wxCoord y = row * square_size;

  wxColour square_color =
      (row + col) % 2 == 0 ? wxColour(185, 182, 174) : wxColour(75, 115, 153);

  dc.SetPen(*wxTRANSPARENT_PEN);

  // Color of the selected pieces square
  if (selected_piece_square == row * 8 + col) {
    square_color = wxColour(255, 255, 0);
    dc.SetPen(wxPen(wxColour(0, 0, 0), 2));
  }

  // Color the legal move squares
  if (is_piece_selected && selected_piece->isLegalMove(row * 8 + col)) {
    square_color = wxColour(191, 227, 180);
    dc.SetPen(wxPen(wxColour(0, 0, 0), 2));
  }

  dc.SetBrush(square_color);

  // Draw the square
  wxRect squareRect(x, y, square_size, square_size);
  dc.DrawRectangle(squareRect);
}

// Draw all the inactive pieces
void Frame::drawInactivePiece(wxPaintDC &dc, int row, int col,
                              wxCoord squareSize) {
  // Don't draw a piece if there is no piece at the current square
  if (chessboard.getBoard()[row * 8 + col] == nullptr) {
    return;
  }

  // Don't draw the selected piece
  if (is_piece_selected && selected_piece_square == row * 8 + col) {
    return;
  }

  wxCoord x = col * squareSize;
  wxCoord y = row * squareSize;

  // Draw the piece
  dc.DrawBitmap(
      chessPieceBitmaps[chessboard.getBoard()[row * 8 + col]->getName()], x, y,
      true);
}

void Frame::drawActivePiece(wxPaintDC &dc) {
  if (!is_piece_selected) {
    return;
  }

  if (selected_piece_square == -1) {
    return;
  }

  char piece = chessboard.getBoard()[selected_piece_square]->getName();
  dc.DrawBitmap(chessPieceBitmaps[piece], mouse_x - 50, mouse_y - 50, true);
}

void Frame::onMouseLeftDown(wxMouseEvent &event) {
  mouse_x = event.GetX();
  mouse_y = event.GetY();

  int square_size = GetClientSize().GetWidth() / 8;

  int clicked_row = mouse_y / square_size;
  int clicked_col = mouse_x / square_size;
  Piece *clicked_piece = chessboard.getBoard()[clicked_row * 8 + clicked_col];

  // If user clicks on an empty square, return
  if (clicked_piece == nullptr) {
    return;
  }

  // If use clicks on piece of different color than turn, return
  if (clicked_piece->getColor() != chessboard.getTurn()) {
    return;
  }

  is_piece_selected = true;
  selected_piece_square = clicked_row * 8 + clicked_col;
  selected_piece = chessboard.getBoard()[selected_piece_square];

  // selected_piece->updateLegalMoves(chessboard.getBoard());

  Refresh();
}

void Frame::onMouseLeftUp(wxMouseEvent &event) {
  if (!is_piece_selected || selected_piece_square == -1 ||
      selected_piece == nullptr) {
    return;
  }

  int square_size = GetClientSize().GetWidth() / 8;

  // Get the square where the mouse was released
  int released_row = mouse_y / square_size;
  int released_col = mouse_x / square_size;
  int released_square = released_row * 8 + released_col;

  chessboard.handleMove(selected_piece_square, released_square);

  Refresh();

  is_piece_selected = false;
  selected_piece = nullptr;
  selected_piece_square = -1;
}

void Frame::onMouseMotion(wxMouseEvent &event) {
  if (is_piece_selected) {
    // Get the mouse coordinates
    mouse_x = event.GetX();
    mouse_y = event.GetY();

    // Refresh the screen
    Refresh();
  }
}

// Exit the application
void Frame::onExit(wxCommandEvent &event) { Close(true); }