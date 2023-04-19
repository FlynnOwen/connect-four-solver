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

    my_game.write_game_state();

    for (int x {0}; x<= 100000; x++){
    
        // Next column to place token
        int column {game_states.gamestates.at(my_game.board.board).to_try.back()};
        game_states.gamestates.at(my_game.board.board).to_try.pop_back();

        //cout << column << endl;
        char result = my_game.place_token(column);
        //cout << result << endl;
        my_game.write_game_state();
        
        column_record.push(column);

        if (result != 'n'){
            back_propogate(result, my_game, column_record, my_game.board);
            undo_move(column_record, my_game);
        };
        while (game_states.gamestates.at(my_game.board.board).to_try.size() == 0){
                undo_move(column_record, my_game);
        };
    };

   game_states.to_json();
    return 0;
}