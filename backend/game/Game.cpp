#include "Game.h"
#include "../board/Board.cpp"
#include <iostream>
#include <string>

using namespace std;

Game::Game() {
    board = Board();
    this->board.writeFenStringToFile(this->board.getFenString());
}

void Game::play() {
    // Start the frontend
    system("python3 frontend/main.py");

    while (this->board.getIsGameOver() == false) {
        this->board.writeFenStringToFile(this->board.getFenString());
    }

    // Reset the FEN string in the file
    system("echo 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1' > text/fen.txt");
}