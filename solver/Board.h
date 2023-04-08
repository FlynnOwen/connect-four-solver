// These are import gaurds
#ifndef _BOARD_H_
#define _BOARD_H_
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Board{
    public:
        vector <vector <int>> board;

        void place_token(int player, int column){
            int row {5};
            while (this->board[column][row] == -1 && row > 0){
                row -= 1;
            };
            this->board[column][row] = player;
        }

    // No args constructor is a fresh game.
    Board()
    : board{{-1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1}}{};

};

#endif