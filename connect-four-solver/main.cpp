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
#include "InputLoader.h"

using namespace std;

int main(){
    // Init randomisation
    random_device rd;
    mt19937 rng {rd()};

    // Load inputs required for game initialisation
    InputArgs init_args {load_inputs()};

    Board my_board;
    GameStates game_states{};
    Game my_game(init_args.ai_token, my_board, game_states);
    int column {-1};
    char result;
    my_game.write_game_state();

    while (true){
        print_board(my_game.board);

        if (my_game.player_turn != init_args.ai_token){
            cout << "Enter a column" << endl;
            cin >> column;
            result = my_game.place_token(column);
            my_game.write_game_state();
        } else {
            simulate(my_game.gamestates, my_game, column, 15000, rng);
            vector<int> gamestate_wins {my_game.gamestates.gamestates.at(my_game.board.board).wins};
            column = max_element(gamestate_wins.begin(), gamestate_wins.end()) - gamestate_wins.begin();
            cout << column << endl;
            result = my_game.place_token(column);
        };
        if (result != 'n'){
            print_board(my_game.board);
            cout << "Game over!" << endl;

            switch (result){
                case 'w':
                    cout << "You Lost!" << endl;
                    break;
                case 'd':
                    cout << "Draw!" << endl;
                    break;
                case 'l':
                    cout << "You Win!" << endl;
                    break;
                };
            
            break;
        };
    };

    return 0;
}