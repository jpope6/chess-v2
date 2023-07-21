#include "frame.h"

using namespace std;

MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Chess", wxDefaultPosition, wxSize(800, 837)) {
  chessboard = Board();
  chessboard.setBoardWithFenString(chessboard.getFenString());
  LoadChessPieces();

  selectedPiece = nullptr;
  pieceSelected = false;

  mouseX = 0;
  mouseY = 0;

  selectedPieceRow = -1;
  selectedPieceCol = -1;

  Bind(wxEVT_PAINT, &MyFrame::OnPaint, this);
  Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

  Bind(wxEVT_LEFT_DOWN, &MyFrame::OnMouseLeftDown, this);
  Bind(wxEVT_LEFT_UP, &MyFrame::OnMouseLeftUp, this);
  Bind(wxEVT_MOTION, &MyFrame::OnMouseMotion, this);
}

// Load the chess piece images
void MyFrame::LoadChessPieces() {
  char pieceNames[] = {'b', 'k', 'n', 'p', 'q', 'r',
                       'B', 'K', 'N', 'P', 'Q', 'R'};

  for (char c : pieceNames) {
    wxBitmap bitmap;

    // file path
    string path = "frame/images/";
    path += c;
    path += ".png";

    bool loadResult = bitmap.LoadFile(path, wxBITMAP_TYPE_PNG);

    // Scale the image to 100x100
    if (loadResult) {
      wxImage image = bitmap.ConvertToImage();
      image.Rescale(100, 100, wxIMAGE_QUALITY_HIGH);
      bitmap = wxBitmap(image);

      getChessPieceBitmaps()[c] = bitmap;
    }
  }
}

// Draw the piece that is being dragged by the mouse
void MyFrame::drawActivePiece(wxPaintDC &dc) {
  // If no piece is selected, don't draw anything
  if (!pieceSelected) {
    return;
  }

  // If row and col have not been set, don't draw anthing
  if (selectedPieceRow == -1 || selectedPieceCol == -1) {
    return;
  }

  // Draw the piece at the mouse's location
  char piece = chessboard.board[selectedPieceRow][selectedPieceCol]->getName();
  dc.DrawBitmap(getChessPieceBitmaps()[piece], mouseX - 50, mouseY - 50, true);
}

// Draw all the other pieces
void MyFrame::drawInactivePiece(wxPaintDC &dc, int row, int col,
                                wxCoord squareSize) {
  // Don't draw a piece if there is no piece at the current square
  if (chessboard.board[row][col] == nullptr) {
    return;
  }

  // Don't draw the selected piece
  if (pieceSelected && row == selectedPieceRow && col == selectedPieceCol) {
    return;
  }

  // get the x and y coordinates of the square
  wxCoord x = col * squareSize;
  wxCoord y = row * squareSize;

  // Draw the piece
  dc.DrawBitmap(getChessPieceBitmaps()[chessboard.board[row][col]->getName()],
                x, y, true);
}

// Draw the squares of the chessboard
void MyFrame::drawSquares(wxPaintDC &dc, int row, int col, wxSize sz,
                          wxCoord squareSize) {
  // get the x and y coordinates of the square
  wxCoord x = col * squareSize;
  wxCoord y = row * squareSize;

  wxColour squareColor =
      (row + col) % 2 == 0 ? wxColour(185, 182, 174) : wxColour(75, 115, 153);

  dc.SetPen(*wxTRANSPARENT_PEN);

  // Determine the color of the square based on row and column
  if (row == selectedPieceRow && col == selectedPieceCol) {
    squareColor = wxColour(255, 255, 0);
    dc.SetPen(wxPen(wxColour(0, 0, 0), 2));
  }

  if (pieceSelected && selectedPiece->isLegalMove(row, col)) {
    squareColor = wxColour(191, 227, 180);
    dc.SetPen(wxPen(wxColour(0, 0, 0), 2));
  }

  dc.SetBrush(squareColor);

  // Draw the square
  wxRect squareRect(x, y, squareSize, squareSize);
  dc.DrawRectangle(squareRect);
}

// The main drawing function
void MyFrame::OnPaint(wxPaintEvent &event) {
  // Create a device context
  wxPaintDC dc(this);

  wxSize sz = GetClientSize();
  wxCoord squareSize = sz.GetWidth() / 8;  // Calculate the size of each square

  // Iterate over the chessboard squares
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      drawSquares(dc, row, col, sz, squareSize);
      drawInactivePiece(dc, row, col, squareSize);
    }

    drawActivePiece(dc);
  }
}

// Select a piece when the mouse is clicked
void MyFrame::OnMouseLeftDown(wxMouseEvent &event) {
  // Get the mouse coordinates
  mouseX = event.GetX();
  mouseY = event.GetY();

  int squareSize = GetClientSize().GetWidth() / 8;

  // Get the row and column of the clicked square
  int clickedCol = mouseX / squareSize;
  int clickedRow = mouseY / squareSize;

  // Check if a piece is present at the clicked position
  // If so, save the row and column of the piece
  if (chessboard.board[clickedRow][clickedCol] != nullptr) {
    selectedPiece = chessboard.board[clickedRow][clickedCol];
    pieceSelected = true;
    selectedPieceRow = clickedRow;
    selectedPieceCol = clickedCol;

    // Update the legal moves of the selected piece
    selectedPiece->updateLegalMoves(chessboard.board);

    chessboard.updateMovesInCheck(chessboard.getBlackKing(), selectedPiece);

    // If Piece is a pawn, update the legal moves for en passant
    if (selectedPiece->isPawn()) {
      int en_passant_row = chessboard.getEnPassantRow();
      int en_passant_col = chessboard.getEnPassantCol();

      if (en_passant_row != -1 && en_passant_col != -1) {
        Pawn *pawn = dynamic_cast<Pawn *>(selectedPiece);
        pawn->updateEnPassant(chessboard.board, en_passant_row, en_passant_col);
      }
    }

    // Handle castling rights
    handleCastlingRights();

    Refresh();
  }
}

// Move the selected piece to the released position
void MyFrame::OnMouseLeftUp(wxMouseEvent &event) {
  if (pieceSelected) {
    // Get the mouse coordinates
    int mouseX = event.GetX();
    int mouseY = event.GetY();

    int squareSize = GetClientSize().GetWidth() / 8;

    // Get the row and column of the released square
    int releasedCol = mouseX / squareSize;
    int releasedRow = mouseY / squareSize;

    // Move the piece
    chessboard.movePiece(selectedPieceRow, selectedPieceCol, releasedRow,
                         releasedCol);
    Refresh();

    // Reset the selected piece data
    pieceSelected = false;
    selectedPieceRow = -1;
    selectedPieceCol = -1;
  }
}

// Move the selected piece with the mouse
void MyFrame::OnMouseMotion(wxMouseEvent &event) {
  if (pieceSelected) {
    // Get the mouse coordinates
    mouseX = event.GetX();
    mouseY = event.GetY();

    // Refresh the screen
    Refresh();
  }
}

// Exit the application
void MyFrame::OnExit(wxCommandEvent &event) { Close(true); }

void MyFrame::handleCastlingRights() {
  if (chessboard.whiteCanCastleKingSide()) {
    chessboard.getWhiteKing()->getPotentialMoves().push_back({7, 6});
  }

  if (chessboard.whiteCanCastleQueenSide()) {
    chessboard.getWhiteKing()->getPotentialMoves().push_back({7, 2});
  }

  if (chessboard.blackCanCastleKingSide()) {
    chessboard.getBlackKing()->getPotentialMoves().push_back({0, 6});
  }

  if (chessboard.blackCanCastleQueenSide()) {
    chessboard.getBlackKing()->getPotentialMoves().push_back({0, 2});
  }
}