#ifndef GAME_H
#define GAME_H

#include "../board/Board.h"

class Game {
    private:
        Board board;
        bool isGameOver = false;

    public:
        // Game constructor
        Game();

        //Getters
        Board getBoard() { return board; }
        bool getIsGameOver() { return isGameOver; }

        void play();
        
};

#endif