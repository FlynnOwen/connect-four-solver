// These are import gaurds
#ifndef _GAME_H_
#define _GAME_H_
#include <string>
#include <iostream>
#include "Board.h"

using namespace std;

class Board{
    public:
        Board board;
        void place_token();

    private:
        int player_turn;

        // Checks whether a draw or win condition has occurred.
        string check_end_game();
        // Checks whether a draw condition has occurred.
        bool check_draw();
        // Checks whether a win condition has occurred.
        int check_win();

        // Checks whether the current game state exists.
        void check_game_state();
        // Writes the current board and turn.
        void write_game_state();
        // Once the game has finished, update gamestate with result.
        void update_end_game_state();
};

#endif