#include "frame.h"

Frame::Frame()
    : wxFrame(nullptr, wxID_ANY, "Chess", wxDefaultPosition, wxSize(800, 837)) {
  this->bot = Bot();
  chessboard = this->bot.getBoard();
  loadChessPieces();

  SetClientSize(800, 800);

  // Create the promotion dialog
  this->promotionDialog =
      new wxDialog(this, wxID_ANY, "Promote Pawn", wxDefaultPosition);
  this->promotionDialog->SetMinSize(wxSize(450, 160));
  this->createPromotionDialog(this->promotionDialog);

  mouse_x = 0;
  mouse_y = 0;

  is_piece_selected = false;
  selected_piece = nullptr;
  selected_piece_square = -1;

  timer = new wxTimer(this, wxID_ANY);
  this->bot_move_made = false;

  Bind(wxEVT_PAINT, &Frame::onPaint, this);
  Bind(wxEVT_MENU, &Frame::onExit, this, wxID_EXIT);
  Bind(wxEVT_TIMER, &Frame::onTimer, this);

  timer->Start(1000);
}

// Load the chess piece images
void Frame::loadChessPieces() {
  char piece_names[] = {'b', 'k', 'n', 'p', 'q', 'r',
                        'B', 'K', 'N', 'P', 'Q', 'R'};

  for (char c : piece_names) {
    wxBitmap bitmap;

    // file path
    string path = "./src/frame/images/" + string(1, c) + ".png";

    bool loadResult = bitmap.LoadFile(path, wxBITMAP_TYPE_PNG);

    int square_size = GetClientSize().GetWidth() / 8;

    // Scale the image to 100x100
    if (loadResult) {
      wxImage image = bitmap.ConvertToImage();
      image.Rescale(square_size, square_size, wxIMAGE_QUALITY_HIGH);
      bitmap = wxBitmap(image);

      chessPieceBitmaps[c] = bitmap;
    }
  }
}

// Create the Promotion Popup and bind the buttons to a promotion function
void Frame::createPromotionDialog(wxDialog *dialog) {
  wxPoint startPos(10, 10);
  int buttonSize = 100;

  // Chess piece images for both colors (WHITE and BLACK)
  vector<char> pieceNames = {'Q', 'R', 'B', 'N'};

  wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

  for (size_t i = 0; i < pieceNames.size(); i++) {
    char pieceName = pieceNames[i];

    // Determine the path based on the current piece name and turn color
    string path = this->chessboard.getTurn() == WHITE
                      ? "./src/frame/images/" + string(1, pieceName) + ".png"
                      : "./src/frame/images/" + string(1, pieceName) + ".png";

    wxBitmap bmp(path, wxBITMAP_TYPE_PNG);
    wxImage image = bmp.ConvertToImage();
    image.Rescale(buttonSize, buttonSize, wxIMAGE_QUALITY_HIGH);
    bmp = wxBitmap(image);

    // Calculate the position of the button based on the index
    wxPoint buttonPos(startPos.x + (i * (buttonSize + 10)), startPos.y);

    // Create the button as a child of the dialog
    wxButton *button = new wxButton(dialog, wxID_ANY, wxEmptyString, buttonPos,
                                    wxSize(buttonSize, buttonSize));
    button->SetBitmap(bmp);

    // Bind the button event to a lambda function that calls promotePawn with
    // the pieceName
    button->Bind(wxEVT_BUTTON,
                 [this, pieceName, dialog](wxCommandEvent &event) {
                   chessboard.promotePawn(pieceName);

                   dialog->EndModal(wxID_OK);

                   Refresh();

                   event.Skip(); // Allow further processing of the event
                 });

    sizer->Add(button, 0, wxALIGN_CENTER | wxALL, 5);
  }

  // Create a vertical box sizer to center the buttons vertically
  wxBoxSizer *verticalCenterSizer = new wxBoxSizer(wxVERTICAL);
  verticalCenterSizer->Add(sizer, 1, wxALIGN_CENTER | wxALL, 10);

  dialog->SetSizerAndFit(verticalCenterSizer);

  dialog->Bind(wxEVT_CLOSE_WINDOW, &Frame::onPromotionDialogClose, this);
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
  if (this->bot.getColor() == this->chessboard.getTurn()) {
    return;
  }

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

  if (chessboard.isPawnPromoting()) {
    promotionDialog->ShowModal();
  }

  this->bot_move_made = false;
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

void Frame::onTimer(wxTimerEvent &event) {
  // Check if it's the bot's turn
  if (this->chessboard.getTurn() == this->bot.getColor() &&
      !this->bot_move_made) {
    this->bot_move_made = true;
    cout << "running" << endl;

    // Call the bot's makeMove function
    pair<int, int> move = this->bot.makeMove();
    this->chessboard.handleMove(move.first, move.second);
    this->bot.setChessboard();

    // Refresh
    Refresh();

    this->bot_move_made = false;
  }
}

void Frame::onPromotionDialogClose(wxCloseEvent &event) {
  chessboard.undoLastMove();
  this->promotionDialog->EndModal(wxID_OK);
  Refresh();
  event.Skip(); // Allow further processing of the event
}

// Exit the application
void Frame::onExit(wxCommandEvent &event) { Close(true); }
