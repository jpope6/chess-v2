import pygame

DARK_SQUARE = (75, 115, 153)
LIGHT_SQUARE = (185, 182, 174)


class Board:
    def __init__(self, window) -> None:
        self.window = window
        self.board = [[None for i in range(8)] for j in range(8)]

        self.chess_notation_letter = {
            0: "a",
            1: "b",
            2: "c",
            3: "d",
            4: "e",
            5: "f",
            6: "g",
            7: "h",
        }

        self.chess_notation_number = {
            0: "8",
            1: "7",
            2: "6",
            3: "5",
            4: "4",
            5: "3",
            6: "2",
            7: "1",
        }

        self.piece_to_image = {
            "r": pygame.transform.scale(
                pygame.image.load("frontend/assets/images/black_rook.png"), (100, 100)
            ),
            "n": pygame.transform.scale(
                pygame.image.load("frontend/assets/images/black_knight.png"), (100, 100)
            ),
            "b": pygame.transform.scale(
                pygame.image.load("frontend/assets/images/black_bishop.png"), (100, 100)
            ),
            "q": pygame.transform.scale(
                pygame.image.load("frontend/assets/images/black_queen.png"), (100, 100)
            ),
            "k": pygame.transform.scale(
                pygame.image.load("frontend/assets/images/black_king.png"), (100, 100)
            ),
            "p": pygame.transform.scale(
                pygame.image.load("frontend/assets/images/black_pawn.png"), (100, 100)
            ),
            "R": pygame.transform.scale(
                pygame.image.load("frontend/assets/images/white_rook.png"), (100, 100)
            ),
            "N": pygame.transform.scale(
                pygame.image.load("frontend/assets/images/white_knight.png"), (100, 100)
            ),
            "B": pygame.transform.scale(
                pygame.image.load("frontend/assets/images/white_bishop.png"), (100, 100)
            ),
            "Q": pygame.transform.scale(
                pygame.image.load("frontend/assets/images/white_queen.png"), (100, 100)
            ),
            "K": pygame.transform.scale(
                pygame.image.load("frontend/assets/images/white_king.png"), (100, 100)
            ),
            "P": pygame.transform.scale(
                pygame.image.load("frontend/assets/images/white_pawn.png"), (100, 100)
            ),
        }

        self.active_piece = None
        self.active_piece_pos = None
        self.turn = None

    def getPieceColor(self, piece):
        if piece.isupper():
            return "w"
        else:
            return "b"

    def getPiece(self, pos):
        row, col = pos[0] // 100, pos[1] // 100

        return self.board[row][col]

    def getPiecePos(self, pos):
        row, col = pos[0] // 100, pos[1] // 100

        return (row, col)

    def movePiece(self, pos):
        if not self.active_piece:
            return False

        row = pos[0] // 100
        col = pos[1] // 100

        # Check if there is a piece in the square
        if self.board[row][col]:
            other_piece = self.board[row][col]

            if self.isDifferentColor(other_piece, self.active_piece):
                self.board[row][col] = None
            else:
                return False

        self.board[row][col] = self.active_piece

        print(self.chess_notation_letter[row] + self.chess_notation_number[col])
        return True

    def isDifferentColor(self, piece1, piece2):
        if piece1.isupper() and piece2.isupper():
            return False

        if piece1.islower() and piece2.islower():
            return False

        return True

    # This can be done better
    def activePiece(self):
        pos = pygame.mouse.get_pos()

        clicked_piece = self.getPiece(pos)

        if self.active_piece and clicked_piece:
            if self.isDifferentColor(clicked_piece, self.active_piece):
                clicked_pos = self.getPiecePos(pos)
                self.board[clicked_pos[0]][clicked_pos[1]] = self.active_piece
                self.board[self.active_piece_pos[0]][self.active_piece_pos[1]] = None
                self.active_piece = None
                self.active_piece_pos = None
            else:
                self.active_piece = clicked_piece
                self.active_piece_pos = self.getPiecePos(pos)
        elif clicked_piece:
            self.active_piece = clicked_piece
            self.active_piece_pos = self.getPiecePos(pos)
        else:
            self.movePiece(pos)
            self.active_piece = None
            self.board[self.active_piece_pos[0]][self.active_piece_pos[1]] = None
            self.active_piece_pos = None

    def drawBoardSquares(self):
        for col in range(len(self.board)):
            for row in range(len(self.board[col])):
                if (row + col) % 2 == 0:
                    pygame.draw.rect(
                        self.window, LIGHT_SQUARE, (row * 100, col * 100, 100, 100)
                    )
                else:
                    pygame.draw.rect(
                        self.window, DARK_SQUARE, (row * 100, col * 100, 100, 100)
                    )

    def loadPieceImage(self, piece, row, col):
        image = self.piece_to_image[piece]
        image_rect = image.get_rect()
        image_rect.center = (row * 100 + 50, col * 100 + 50)
        self.window.blit(image, image_rect)

    def populateBoardWithFen(self, fen_string):
        fen_board = fen_string.split(" ")[0]
        turn = fen_string.split(" ")[1]

        self.turn = turn

        row = 0
        col = 0

        for c in fen_board:
            if c == "/":
                col += 1
                row = 0
            else:
                if c.isdigit():
                    while row < int(c):
                        self.board[row][col] = None
                        row += 1
                else:
                    self.board[row][col] = c

                    row += 1

    def drawPieces(self):
        for row in range(len(self.board)):
            for col in range(len(self.board[row])):
                if self.board[row][col]:
                    self.loadPieceImage(self.board[row][col], row, col)

    def draw(self):
        self.drawBoardSquares()
        self.drawPieces()
