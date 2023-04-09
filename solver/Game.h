// These are import gaurds
#ifndef _GAME_H_
#define _GAME_H_
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "Board.h"

using namespace std;

class Game{
    public:
        Board board;
        vector <int> place_token(int player, int column){
            int row {this->board.place_token(player, column)};
            
            //this->prev_column = column;
            this->player_turn = player;
            return {row, column};
        };

        // No args constructor - game can start with any board config.
        Game(Board board_val)
        : board{board_val}{};

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
        bool check_win(int row, int column){
            
            bool win = 
            _check_horizontal_win(row, column) 
            || _check_vertical_win(row, column) 
            || _check_left_diagonal_win(row, column)
            || _check_right_diagonal_win(row, column);
            
            return win;
        };

    private:
        int player_turn;
        int prev_column {-1};

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
            int left_column {column - 1};
            int right_column {column + 1};

            while (this->board.board[left_column][row] == this->player_turn && left_column >= 0){
                left_column -= 1;
                total_count += 1;
            };

            while (this->board.board[right_column][row] == this->player_turn && right_column <= 6){
                right_column += 1;
                total_count += 1;
            };

            if (total_count >= 4){
                return true;
            };
            return false;
        };

        bool _check_left_diagonal_win(int row, int column){
            int total_count {1};
            int left_column {column - 1};
            int left_row {row - 1};
            int right_column {column + 1};
            int right_row {row + 1};

            while (this->board.board[left_column][left_row] == this->player_turn && left_column >= 0 && left_row >= 0){
                left_column -= 1;
                left_row -= 1;
                total_count += 1;
            };

            while (this->board.board[right_column][right_row] == this->player_turn && right_column <= 6 && right_row <= 5){
                right_column += 1;
                right_row += 1;
                total_count += 1;
            };

            if (total_count >= 4){
                return true;
            };
            return false;
        };

        bool _check_right_diagonal_win(int row, int column){
            int total_count {1};
            int left_column {column - 1};
            int left_row {row + 1};
            int right_column {column + 1};
            int right_row {row - 1};

            while (this->board.board[left_column][left_row] == this->player_turn && left_column >= 0 && left_row <= 5){
                left_column -= 1;
                left_row += 1;
                total_count += 1;
            };

            while (this->board.board[right_column][right_row] == this->player_turn && right_column <= 6 && right_row >= 0){
                right_column += 1;
                right_row -= 1;
                total_count += 1;
            };

            if (total_count >= 4){
                return true;
            };
            return false;
        };

        // Checks whether a draw or win condition has occurred.
        string check_end_game();

        // Checks whether the current game state exists.
        void check_game_state();
        // Writes the current board and turn.
        void write_game_state();
        // Once the game has finished, update gamestate with result.
        void update_end_game_state();

};

#endif