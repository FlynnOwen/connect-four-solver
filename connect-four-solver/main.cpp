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
    mt19937 rng {rd()};

    // init game vars
    Board my_board;
    GameStates game_states{};

    // AI starts first with arg 'X', human with arg 'O'
    char turn_input;
    cout << "Would you like to take the first turn? y/n" << endl;
    cin >> turn_input;

    char ai_token;
    if (turn_input == 'y'){
        ai_token = 'O';
    } else {
        ai_token = 'X';
    };

    Game my_game(ai_token, my_board, game_states);
    int column {-1};
    char result;
    my_game.write_game_state();

    while (true){
        print_board(my_game.board);

        if (my_game.player_turn != ai_token){
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