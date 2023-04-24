#ifndef _SIMUTILS_H_
#define _SIMUTILS_H_
#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <random>
#include <map>
#include "Board.h"
#include "Game.h"
#include "GameState.h"

#define RESET "\033[0m"
#define YELLOW "\033[33m"
#define RED "\033[31m"

using namespace std;

void print_board(Board board){
    // Clears the terminal, and prints the current board config with 
    // different colours for each token.
    //system("clear");
    cout << " 0 1 2 3 4 5 6  " << endl;
    cout << "---------------" << endl;
    for (int i {0}; i <= 5; i++){
        cout << '|';
        for (int j {0}; j <= 6; j++){
            if (board.board[i][j] == 'O'){
                cout << YELLOW << board.board[i][j] << RESET;
            } else {
                cout << RED << board.board[i][j] << RESET;
            };
            cout << "|";
        };
        cout << endl;
        cout << "---------------" << endl;
    };
    cout << " 0 1 2 3 4 5 6  " << endl;
    cout << endl;
};


void back_propogate(char result, 
                    Game& game_ref,
                    stack<int>& column_record_ref,
                    Board& board_ref){
    
    int ai_col {-1};
    // undo all moves and update gamestate with the result at each undo.
    while (column_record_ref.size() > 0){
        int i = 0;
        int j = column_record_ref.top();

        column_record_ref.pop();
        while (board_ref.board[i][j] == ' '){
            i++;
        };
        
        // Gamestate only exists on human player turns
        if (board_ref.board[i][j] != game_ref.ai_player){
            if (ai_col != -1){
                switch (result){
                    case 'w':
                        game_ref.gamestates.gamestates.at(board_ref.board).wins[ai_col] += 1;
                        break;
                    case 'd':
                        game_ref.gamestates.gamestates.at(board_ref.board).draws[ai_col] += 1;
                        break;
                    case 'l':
                        game_ref.gamestates.gamestates.at(board_ref.board).losses[ai_col] += 1;
                        break;
                };
            };
        } else {
            ai_col = j;
        };
        if (column_record_ref.size() != 0){
            board_ref.board[i][j] = ' ';
        };
    };
};


// remove places a token can't be placed
set<int> check_placement_options(Board& board_ref){
    set<int> options;

    for (int j {0}; j <= 6; j++){
        if (board_ref.board[0][j] == ' '){
            options.insert(j);
        };
    };

    return options;
};


int calculate_best_node_ucb(GameState game_state, double C, set<int> column_options){
    // Given a gamestate, calculates the best column to place a token in, using the UCB formula
    // where ucb[i] = wins[i]/total_sims[i] + C* sqrt(log(sum(total_sims))/total_sims[i])
    map<int, double> total_ucbs;
    int total_sims {reduce(game_state.wins.begin(), game_state.wins.end()) 
                  + reduce(game_state.draws.begin(), game_state.draws.end()) 
                  + reduce(game_state.losses.begin(), game_state.losses.end())};
    
    for (int i: column_options){
        int wins_node {game_state.wins[i]};
        // Cast to double to use division in UCB calculation
        double sims_node {static_cast<double>(wins_node) + game_state.draws[i] + game_state.losses[i]};

        double ucb_node {(wins_node/sims_node) + (C * sqrt(log(total_sims)/sims_node))};
        if (isnan(ucb_node)){
            ucb_node = INFINITY;
        }
        total_ucbs[i] = ucb_node;
    };

    //auto best_node {max_element(total_ucbs.begin(),total_ucbs.end(),[] (const pair<char,int>& a, const pair<char,int>& b)->bool{ return a.second < b.second; })->first};
    int best_node = max_element(total_ucbs.begin(), total_ucbs.end(), [](const auto &x, const auto &y){return x.second < y.second;})->first;

    return best_node;
};


void simulate(GameStates& game_states_ref,
              Game game,
              int column,
              int num_games,
              mt19937 rng){
    // Perform simulation given a board configuration.
    char player_turn {game.player_turn};

    // Simulate num_games games
    stack<int> column_record;
    if (column == -1){
        game.write_game_state();
    }

    // Generate a column by evaluating UCB
    // Finish the game and back-propogate to input gamestate
    for (int i {0}; i <= num_games; i++){
        if (column != -1){
            column_record.push(column);
        };

        while (true){
            // possible columns to place token
            set <int> options {check_placement_options(game.board)};
            if (game.player_turn != game.ai_player){
                cout << "h1" << endl;
                vector<int> columns;
                sample(options.begin(), options.end(), back_inserter(columns), 1, rng);
                int column = columns[0];
                char result = game.place_token(column);
                game.write_game_state();
                column_record.push(column);
                if (result != 'n'){
                    back_propogate(result, game, column_record, game.board);
                    break;
                };
                cout << "h2" << endl;
            } else {
                cout << "h3" << endl;
                GameState game_state {game_states_ref.gamestates.at(game.board.board)};
                // TODO: Move C value to argument
                cout << "h3.5" << endl;
                int column {calculate_best_node_ucb(game_state, sqrt(2), options)};
                char result = game.place_token(column);
                column_record.push(column);
                if (result != 'n'){
                    back_propogate(result, game, column_record, game.board);
                    break;
                };
                cout << "h4" << endl;
            };
            //cout << result << endl;
            print_board(game.board);
        };
    game.player_turn = player_turn;
    };
};
#endif