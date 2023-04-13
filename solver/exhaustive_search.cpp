#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <stack>
#include "Board.h"
#include "Game.h"
#include "GameState.h"

using namespace std;

void print_board(Board board){
    for (int i {0}; i <= 6; i++){
        for (int j {0}; j <= 5; j++){
            cout << board.board[i][j];
        };
        cout << endl;
    };
    cout << endl;
};

void push_vector_stack(stack<int>& stack_ptr, vector<int> vector_val){
    // Appends a vector object to a stack object
    for (long unsigned int i {0}; i <= vector_val.size(); i++){
        stack_ptr.push(vector_val[i]);
    }
};

void undo_move(stack <int>& column_record_ref, vector<vector<int>>& board_ref){
    // Removes a token from a board
    int row {5};
    int column {column_record_ref.top()};
    column_record_ref.pop();

    while (board_ref[column][row] == -1){
        row -= 1;
    }
    cout << row << endl;
    cout << column << endl;
    board_ref[column][row] = -1;
};

void backtrack_game(){

};

int main(){
    // Opt for breadth or depth first search?
    Board my_board;
    GameStates game_states{};
    Game my_game(my_board, game_states);

    // Record of columns tokens were placed in to allow back-tracking
    stack<int> column_record;
    stack<int> turn_record;

    my_game.write_game_state();
    
    // Next column to place token
    int column {game_states.gamestates.at(my_game.board.board).to_try.back()};
    game_states.gamestates.at(my_game.board.board).to_try.pop_back();
    cout << column << endl;
    vector<int> placement = my_game.place_token(column);
    cout << my_game.check_win(placement[0], placement[1]) << endl;
    cout << my_game.check_draw() << endl;
    my_game.write_game_state();
    cout << my_game.check_game_state() << endl;
    
    // The most recent column placed
    column_record.push(column);
    turn_record.push(my_game.player_turn);
    cout << game_states.gamestates.at(my_game.board.board).to_try.back() << endl;

    // Undo the move
    print_board(my_game.board);
    undo_move(column_record, my_game.board.board);
    print_board(my_game.board);
    
    return 0;
}