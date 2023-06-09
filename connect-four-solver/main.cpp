#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "board.h"
#include "game.h"
#include "gamestate.h"
#include "utils.h"
#include "montecarlotreesearch.h"
#include "inputloader.h"

using namespace std;

// Main function for gameplay.
// A game is played between a human player, using stdin to input columns,
// and an AI using MCTS to generate moves and place tokens.
int main()
{
    InputArgs init_args{};

    random_device rd;
    mt19937 rng{rd()};
    Board my_board;
    GameStates game_states{};
    Game my_game(init_args.ai_token, my_board, game_states);

    int column{-1};
    char result;

    while (true)
    {
        print_board(my_game.board);

        if (my_game.player_turn != init_args.ai_token)
        {

            if (init_args.trash_talk)
            {
                generate_trash_talk();
            };

            cout << "Enter a column" << endl;
            cin >> column;
            result = my_game.place_token(column);
            my_game.write_game_state();
        }
        else
        {

            simulate(my_game.gamestates, my_game, column, init_args.difficulty, rng);
            
            vector<int> gamestate_games {my_game.gamestates.gamestates.at(my_game.board.board).games};
            column = max_element(gamestate_games.begin(), gamestate_games.end()) - gamestate_games.begin();
            result = my_game.place_token(column);
        };
        if (result != 'n')
        {

            print_board(my_game.board);
            cout << "Game over!" << endl;

            switch (result)
            {
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