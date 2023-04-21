#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <stack>
#include <random>
#include "Board.h"
#include "Game.h"
#include "GameState.h"
#include "SimUtils.h"

using namespace std;

int main(){
    // Init randomisation
    random_device rd;
    mt19937 rng(rd());

    // Opt for breadth or depth first search?
    Board my_board;
    GameStates game_states{};
    Game my_game(my_board, game_states);

    // Record of columns tokens were placed in to allow back-tracking
    stack<int> column_record;
    stack<int> turn_record;

    my_game.write_game_state();

    for (int x {0}; x<= 1000000; x++){
        unsigned long index_choices {game_states.gamestates.at(my_game.board.board).to_try.size() - 1};
        uniform_int_distribution<int> uni(0, index_choices);
        auto index = uni(rng);

        // Next column to place token
        int column {game_states.gamestates.at(my_game.board.board).to_try.at(index)};

        char result = my_game.place_token(column);
        
        // The most recent column placed
        column_record.push(column);

        if (result != 'n'){
            back_propogate(result, my_game, column_record, my_game.board);
            while (column_record.size() != 0){
                undo_move(column_record, my_game);
            };
        } else {
            my_game.write_game_state();
        };
    };

   game_states.to_json();
    return 0;
}