import pygame

DARK_SQUARE = (75, 115, 153)
LIGHT_SQUARE = (185, 182, 174)


class Board:
    def __init__(self, window) -> None:
        self.window = window
        self.board = [[None for i in range(8)] for j in range(8)]

        self.piece_to_image = {
            "r": "frontend/assets/images/black_rook.png",
            "n": "frontend/assets/images/black_knight.png",
            "b": "frontend/assets/images/black_bishop.png",
            "q": "frontend/assets/images/black_queen.png",
            "k": "frontend/assets/images/black_king.png",
            "p": "frontend/assets/images/black_pawn.png",
            "R": "frontend/assets/images/white_rook.png",
            "N": "frontend/assets/images/white_knight.png",
            "B": "frontend/assets/images/white_bishop.png",
            "Q": "frontend/assets/images/white_queen.png",
            "K": "frontend/assets/images/white_king.png",
            "P": "frontend/assets/images/white_pawn.png",
        }

    def drawBoardSquares(self):
        for row in range(len(self.board)):
            for col in range(len(self.board[row])):
                if (row + col) % 2 == 0:
                    pygame.draw.rect(
                        self.window, LIGHT_SQUARE, (row * 100, col * 100, 100, 100)
                    )
                else:
                    pygame.draw.rect(
                        self.window, DARK_SQUARE, (row * 100, col * 100, 100, 100)
                    )

    def drawPieces(self, fen_string):
        fen_board = fen_string.split(" ")[0]

        row = 0
        col = 0

        for c in fen_board:
            if c == "/":
                row += 1
                col = 0
            else:
                if c.isdigit():
                    while col < int(c):
                        self.board[row][col] = None
                        col += 1
                else:
                    self.board[row][col] = c

                    image = pygame.transform.scale(
                        pygame.image.load(self.piece_to_image[c]), (100, 100)
                    )

                    image_rect = image.get_rect()
                    image_rect.center = (col * 100 + 50, row * 100 + 50)
                    self.window.blit(image, image_rect)

                    col += 1

    def draw(self, fen_string):
        self.drawBoardSquares()
        self.drawPieces(fen_string)
