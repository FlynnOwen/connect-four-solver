// These are import gaurds
#ifndef _BOARD_H_
#define _BOARD_H_
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Board{
    public:
        vector <vector <char>> board;

        int place_token(char player, int column){
            int row {5};
            while (this->board[column][row] == ' ' && row >= 0){
                row -= 1;
            };
            this->board[column][row + 1] = player;

            return row  + 1;
        };

    // No args constructor is a fresh game.
    Board()
    : board{{' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' '},}{};

};

#endif