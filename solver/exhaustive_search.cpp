#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <stack>
#include "Board.h"
#include "Game.h"
#include "GameState.h"
#include "SimUtils.h"

using namespace std;

int main(){
    // Opt for breadth or depth first search?
    Board my_board;
    GameStates game_states{};
    Game my_game(my_board, game_states);

    // Record of columns tokens were placed in to allow back-tracking
    stack<int> column_record;
    stack<int> turn_record;

    my_game.write_game_state();

    for (int x {0}; x<= 10000; x++){
    
        // Next column to place token
        int column {game_states.gamestates.at(my_game.board.board).to_try.back()};
        game_states.gamestates.at(my_game.board.board).to_try.pop_back();

        //cout << column << endl;
        char result = my_game.place_token(column);
        //cout << result << endl;
        my_game.write_game_state();
        
        // The most recent column placed
        column_record.push(column);
        turn_record.push(my_game.player_turn);
        //print_board(my_game.board);

        if (result != 'n'){
            back_propogate(result, my_game, column_record, my_game.board);
            undo_move(column_record, my_game);
        };
        while (game_states.gamestates.at(my_game.board.board).to_try.size() == 0){
                undo_move(column_record, my_game);
        };
        //cout << game_states.gamestates.at(my_game.board.board).to_try.size() << endl;
        
        //cout << x << endl;
    };

    /*

    while (game_states.gamestates.at(my_game.board.board).to_try.size() == 0){
        undo_move(column_record, my_game);
    };

    print_board(my_game.board);
    */
    return 0;
}