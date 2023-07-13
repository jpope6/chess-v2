#include "Game.h"
#include "../board/Board.cpp"
#include <iostream>
#include <string>

using namespace std;

Game::Game() {
    board = Board();
    system("python3 frontend/main.py");
    this->play();
}

void Game::play() {
    while (!this->getIsGameOver()) {
        this->getBoard().printBoard();
        cout << endl << "Enter a move: ";
        string move;
        cin >> move;

        this->getBoard().writeFenStringToFile(move);

        if (move == "exit") {
            this->isGameOver = true;
        }
    }
}