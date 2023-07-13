#ifndef GAME_H
#define GAME_H

#include "../board/Board.h"

class Game {
    private:
        Board board;

    public:
        // Game constructor
        Game();

        //Getters
        Board getBoard() { return board; }

        void play();
        
};

#endif