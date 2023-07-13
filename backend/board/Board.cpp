#include "Board.h"
#include <iostream>
#include <fstream>

using namespace std;

// Board constructor
Board::Board() {
    this->fen_string = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    this->isGameOver = false;
    this->writeFenStringToFile(this->getFenString());
    this->setBoardWithFenString(this->getFenString());
}

// Set the board with the FEN string
void Board::setBoardWithFenString(string fen_string) {
    // Get the board part of the FEN string
    string fen_board = fen_string.substr(0, fen_string.find(" "));

    int row = 0;
    int col = 0;

    // Loop through the FEN board string
    for (char c : fen_board) {

        if (c == '/') { // If we reach the end of a row
            row++; 
            col = 0;
        } else {
            if (isdigit(c)) { // If the character is a number
                int num = c - '0';

                // Fill the empty squares with spaces
                while (col < num) {
                    // this->board[row][col] = this->getPieceArt()[' ']; 
                    col ++;
                }
            } else {
                // Fill the squares with the piece art
                // this->board[row][col] = this->getPieceArt()[c];
                col++;
            }
        }

    }
}

void Board::writeFenStringToFile(string fen_string) {    
    fstream file;

    file.open("text/fen.txt");
    
    // read the line in the file
    string fen = "";
    getline(file, fen);

    if (fen == "exit" && this->isGameOver == false) {
        file.close();
        this->isGameOver = true;
    }


    file << fen_string;
    file.close();
}

void Board::printBoard() {
    // Print the column letters
    cout << endl << "   a b c d e f g h" << endl;
    cout << "  _________________" << endl;
    
    for (int i = 0; i < 8; i++) {

        cout << 8 - i << "| "; // Print the row numbers

        for (int j = 0; j < 8; j++) {

            if (j == 7) {  // If we reach the end of the row
                cout << this->board[i][j];
            } else { // If we are not at the end of the row
                cout << this->board[i][j] << " ";
            }

        }

        cout << " |" << 8 - i << endl; // Print the row numbers

    }
    
    // Print the column letters
    cout << "  ⎻⎻⎻⎻⎻⎻⎻⎻⎻⎻⎻⎻⎻⎻⎻⎻⎻" << endl;
    cout << "   a b c d e f g h" << endl << endl;
}