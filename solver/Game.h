// These are import gaurds
#ifndef _GAME_H_
#define _GAME_H_
#include <string>
#include <iostream>
#include <cstdlib>
#include "Board.h"

using namespace std;

class Game{
    public:
        Board board;
        void place_token(int player, int column){
            this->board.board[column].push_back(player);
            this->prev_column = column;
            this->player_turn = abs(player - 1);
        };

        // No args constructor - game can start with any board config.
        Game(Board board_val)
        : board{board_val}{};

    private:
        int player_turn;
        int prev_column {-1};

        // Checks whether a draw or win condition has occurred.
        string check_end_game(){
        };

        // Checks whether a draw condition has occurred.
        bool check_draw(){
            for (int i {0}; i <= 6; i++){
                for (int j {0}; j <= 5; j++){
                    if (this->board.board[i][j] == -1){
                        return false;
                    };
                };
            };
            return true;
        };

        // Checks whether a win condition has occurred.
        int check_win(){
            int row {6};
            int column {this->prev_column};

            while (this->board.board[column][row] != -1){
                row -= 1;
            };
        };

        bool _check_vertical_win(int row, int column){
            // Checks whether 4 tokens are stacked consecutively vertically.
            int total_count {1};

            while (this->board.board[column][row] == this->player_turn && row >= 0 && total_count != 4){
                row  -= 1;
                total_count += 1;
            };

            if (total_count == 4){
                return true;
            };

            return false;
        };

        bool _check_horizontal_win(int row, int column){
            // Checks whether 4 or more tokens are consectively horizontally adjacent.
            int total_count {1};
            int left_column {row - 1};
            int right_column {row + 1};

            while (left_column == this->player_turn && left_column >= 0){
                left_column -= 1;
                total_count += 1;
            };

            while (right_column == this->player_turn && right_column >= 0){
                right_column += 1;
                total_count += 1;
            };

            if (total_count >= 4){
                return true;
            };
            return false;
        };

        bool _check_left_diagonal_win(int row, int column);
        bool _check_right_diagonal_win(int row, int column);

        // Checks whether the current game state exists.
        void check_game_state();
        // Writes the current board and turn.
        void write_game_state();
        // Once the game has finished, update gamestate with result.
        void update_end_game_state();

};

#endif