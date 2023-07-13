import pygame


class Board:
    def __init__(self, window) -> None:
        self.window = window
        self.board = [[None for i in range(8)] for j in range(8)]

    def drawBoardSquares(self):
        for row in range(len(self.board)):
            for col in range(len(self.board[row])):
                if (row + col) % 2 == 0:
                    pygame.draw.rect(
                        self.window, (255, 255, 255), (row * 100, col * 100, 100, 100)
                    )
                else:
                    pygame.draw.rect(
                        self.window, (0, 0, 0), (row * 100, col * 100, 100, 100)
                    )

    def drawPieces(self, fen_string):
        pass

    def draw(self):
        self.drawBoardSquares()
