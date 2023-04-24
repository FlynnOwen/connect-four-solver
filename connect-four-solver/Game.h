#ifndef _GAME_H_
#define _GAME_H_
#include <string>
#include <cstdlib>
#include <vector>
#include "Board.h"
#include "GameState.h"

using namespace std;

class Game{

    public:
        char ai_player;
        char player_turn {'X'};
        Board board;
        GameStates& gamestates;
        
        char place_token(int column){
            // Places a token and checks for win, draw or loss
            int row {this->board.place_token(this->player_turn, column)};
            char retval;

            bool win {check_win(row, column)};
            bool draw {check_draw()};
            
            if (win){
                if (this->player_turn == this->ai_player){
                    retval = 'w';
                } else {
                    retval = 'l';
                };
            } else if (draw){
                retval = 'd';
            } else {
                retval = 'n';
            };

            switch (player_turn)
            {
            case 'X':
                this->player_turn = 'O';
                break;
            case 'O':
                this->player_turn = 'X';
                break;
            };
            return retval;
        };

        // 
        Game(
            // AI starts first with arg 'X', human with arg 'O'
            char ai_player_val,
            Board board_val, 
            GameStates& gamestates_ref)
        : ai_player{ai_player_val},
          board{board_val}, 
          gamestates{gamestates_ref}{};

        // Checks whether a draw condition has occurred.
        bool check_draw(){
            for (int i {0}; i <= 5; i++){
                for (int j {0}; j <= 6; j++){
                    if (this->board.board[i][j] == ' '){
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

        // Writes the current board and turn.
        void write_game_state(){
            GameState game_state {this->player_turn};
            if (!check_game_state()){
                this->gamestates.gamestates.insert({this->board.board, game_state});
            }
        };

        // Checks whether the current game state exists.
        bool check_game_state(){
            return this->gamestates.gamestates.count(this->board.board);
        };

    private:

        bool _check_vertical_win(int row, int column){
            // Checks whether 4 tokens are stacked consecutively vertically.
            int total_count {0};

            while (row >= 0  && this->board.board[row][column] == this->player_turn && total_count != 4){
                total_count += 1;
                row  -= 1;
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

            while (left_column >= 0 && this->board.board[row][left_column] == this->player_turn){
                total_count += 1;
                left_column -= 1;
            };

            while (right_column <= 6 && this->board.board[row][right_column] == this->player_turn){
                total_count += 1;
                right_column += 1;
            };
            
            if (total_count >= 4){
                //cout << "horiztonal" << endl;
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

            while (left_column >= 0 && left_row >= 0 && this->board.board[left_row][left_column] == this->player_turn){
                left_column -= 1;
                left_row -= 1;
                total_count += 1;
            };

            while (right_column <= 6 && right_row <= 5 && this->board.board[right_row][right_column] == this->player_turn){
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

            while (left_column > 0 && left_row <= 5 && this->board.board[left_row][left_column] == this->player_turn){
                left_column -= 1;
                left_row += 1;
                total_count += 1;
            };

            while (right_column < 6 && right_row >= 0 && this->board.board[right_row][right_column] == this->player_turn){
                right_column += 1;
                right_row -= 1;
                total_count += 1;
            };

            if (total_count >= 4){
                return true;
            };
            return false;
        };
};

#endif