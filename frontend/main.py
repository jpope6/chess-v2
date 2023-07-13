import pygame
from board import Board


class Game:
    def __init__(self):
        pygame.init()
        self.width = 800
        self.height = 800
        self.window = pygame.display.set_mode((self.width, self.height))
        pygame.display.set_caption("Chess")
        self.clock = pygame.time.Clock()

        self.fen_string = self.getFenString()
        self.board = Board(self.window)
        self.board.populateBoardWithFen(self.fen_string)

    def getFenString(self):
        f = open("text/fen.txt", "r")
        fen = f.read()
        f.close()
        return fen

    def setFenString(self):
        fen = self.board.updateFenString()
        f = open("text/fen.txt", "w")
        f.write(fen)
        f.close()

    def play(self):
        self.window.fill((255, 255, 255))

        running = True
        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                if event.type == pygame.MOUSEBUTTONDOWN:
                    self.board.handleActivePiece()

            fen = self.getFenString()

            # This way we don't have to parse the fen string every frame
            if fen != self.fen_string:
                self.fen_string = fen
                self.board.populateBoardWithFen(self.fen_string)

            self.board.draw()

            self.clock.tick(60)
            # Update the display
            pygame.display.update()


# Quit Pygame
pygame.quit()


def main():
    game = Game()
    game.play()


if __name__ == "__main__":
    main()
