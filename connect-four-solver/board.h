// These are import gaurds
#ifndef _BOARD_H_
#define _BOARD_H_
#include <string>
#include <iostream>
#include <vector>

using namespace std;

// Class that encapsulates the connect 4 board as a 6 x 7 matrix of characters.
class Board
{
public:
    vector<vector<char>> board;

    // Given a player 'X' or 'O', will place a token in the specified column.
    int place_token(char player, int column)
    {
        int row{0};
        while (row <= 5 && this->board[row][column] == ' ')
        {
            row += 1;
        };
        this->board[row - 1][column] = player;

        return row - 1;
    };

    // No args constructor is a new game.
    Board()
        : board{{' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' ', ' ', ' ', ' '}} {};
};

#endif