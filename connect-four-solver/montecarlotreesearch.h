#ifndef _MONTECARLOTREESEARCH_H_
#define _MONTECARLOTREESEARCH_H_
#include <vector>
#include <stack>
#include <random>
#include <set>
#include <map>
#include <algorithm>
#include "board.h"
#include "game.h"
#include "gamestate.h"
#include "utils.h"

// Constant used to balance exploration vs exploitation in UCB formula.
#define C sqrt(2)

using std::vector;
using std::stack;
using std::set;
using std::isnan;
using std::max_element;
using std::sample;

// Performs backpropogation from MCTS.
// Iterate through a stack that is previous column placements of tokens, removing
// each token, and updating a node in the gametree (Gamestate) with the result
// of the completed Game.
void back_propogate(char result,
                    Game &game_ref,
                    stack<int> &column_record_ref,
                    Board &board_ref)
{

    int ai_col{-1};

    while (column_record_ref.size() > 0)
    {

        int i = 0;
        int j = column_record_ref.top();
        column_record_ref.pop();

        while (board_ref.board[i][j] == ' ')
        {
            i++;
        };

        // Gamestate only exists on human player turns
        if (board_ref.board[i][j] != game_ref.ai_player)
        {

            if (ai_col != -1)
            {
                switch (result)
                {
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
                game_ref.gamestates.gamestates.at(board_ref.board).games[ai_col] += 1;
            };
        }
        else
        {
            ai_col = j;
        };

        if (column_record_ref.size() != 0)
        {
            board_ref.board[i][j] = ' ';
        };
    };
};

// Performs selection from MCTS.
// Given a node in the gametree (a Gamestate), calculates the best column to place a token in, using the UCB formula.
// where ucb[i] = wins[i]/total_sims[i] + C*sqrt(log(sum(total_sims))/total_sims[i])
// Unsearched nodes have a UCB value of infinity - this prioritzes unsearch nodes.
int select(GameState game_state, set<int> column_options)
{

    map<int, double> total_ucbs;
    int total_sims{reduce(game_state.games.begin(), game_state.games.end())};

    for (int i : column_options)
    {

        int wins_node{game_state.wins[i]};
        double sims_node{static_cast<double>(wins_node) + game_state.draws[i] + game_state.losses[i]};
        double ucb_node{(wins_node / sims_node) + (C * sqrt(log(total_sims) / sims_node))};

        // Unsearched nodes are assigned UCB = infinity
        if (isnan(ucb_node))
        {
            ucb_node = INFINITY;
        };

        total_ucbs[i] = ucb_node;
    };

    int best_node = max_element(total_ucbs.begin(), total_ucbs.end(), [](const auto &x, const auto &y)
                                { return x.second < y.second; })
                        ->first;

    return best_node;
};

// Performs simulation from MCTS.
// For a given gametree node (GameState),
// the game is played until completion, being either a win, draw, or loss
// for the AI. Once the game is complete, backpropogation is performed.
// This is repeated num_games times, building a well-informed game tree, for which the
// next true move can be chosen by the AI.
void simulate(GameStates &game_states_ref,
              Game game,
              int column,
              int num_games,
              mt19937 rng)
{

    char player_turn{game.player_turn};
    stack<int> column_record;
    int sim_column;

    for (int i{0}; i <= num_games; i++)
    {
        char result;
        column_record.push(column);

        while (true)
        {
            set<int> options{check_placement_options(game.board)};

            if (game.player_turn != game.ai_player)
            {

                // Generate a column from an equally weighted categorical distribution.
                vector<int> columns;
                sample(options.begin(), options.end(), back_inserter(columns), 1, rng);
                sim_column = columns[0];
                result = game.place_token(sim_column);
                game.write_game_state();
                column_record.push(sim_column);
            }
            else
            {

                // Generate a column using 'selection' (evaluating the UCB).
                GameState game_state{game_states_ref.gamestates.at(game.board.board)};
                sim_column = select(game_state, options);
                result = game.place_token(sim_column);
                column_record.push(sim_column);
            };

            if (result != 'n')
            {
                back_propogate(result, game, column_record, game.board);
                break;
            };
        };

        game.player_turn = player_turn;
    };
};
#endif