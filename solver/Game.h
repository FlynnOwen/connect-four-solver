// These are import gaurds
#ifndef _GAME_H_
#define _GAME_H_
#include <string>
#include <iostream>
#include "Board.h"

using namespace std;

class Game{
    public:
        Board board;
        void place_token(int player, int column){
            this->board.board[column].push_back(player);
        };

        // No args constructor - game can start with any board config.
        Game(Board board_val)
        : board{board_val}{};

    private:
        int player_turn;

        // Checks whether a draw or win condition has occurred.
        string check_end_game();

        // Checks whether a draw condition has occurred.
        bool check_draw(){
            for (int i {0}; i <= 6; i++){
                if (this->board.board[i].size() != 7){
                    return false;
                };
            };

            return true;
        };

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