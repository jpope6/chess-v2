#include "board/Board.cpp"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    Board board;

    // run the frontend in python
    system("python3 frontend/main.py");

    bool gameOver = false;

    while (!gameOver) {
        board.printBoard();
        cout << endl << "Enter a move: ";
        string move;
        cin >> move;

        board.writeFenStringToFile(move);

        if (move == "exit") {
            gameOver = true;
        }
    }
    
    return 0;
}
