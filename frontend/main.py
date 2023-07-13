import pygame
from board import Board


class Game:
    def __init__(self):
        pygame.init()
        self.width = 800
        self.height = 800
        self.window = pygame.display.set_mode((self.width, self.height))
        pygame.display.set_caption("Chess")

        self.board = Board(self.window)

    def getFenString(self):
        f = open("fen.txt", "r")
        fen = f.read()
        f.close()
        return fen

    def play(self):
        self.window.fill((255, 255, 255))

        running = True
        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False

            fen = self.getFenString()

            self.board.draw(fen)

            # Update the display
            pygame.display.flip()


# Quit Pygame
pygame.quit()


def main():
    game = Game()
    game.play()


if __name__ == "__main__":
    main()
