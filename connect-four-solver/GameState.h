#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_
#include <vector>
#include <map>
#include <string>
#include "board.h"

using namespace std;

// A single node in the gametree of MCTS. It includes the number
// of wins, draws, and lossses for each potential column placement
// directly following this gamestate.
class GameState
{
public:
    char player_turn;
    // count of wins, draws and losses per possible column.
    vector<int> wins{0, 0, 0, 0, 0, 0, 0};
    vector<int> draws{0, 0, 0, 0, 0, 0, 0};
    vector<int> losses{0, 0, 0, 0, 0, 0, 0};

    GameState(char player_turn_val)
        : player_turn{player_turn_val} {};
};

// Gamestates is the gametree from MCTS, represented as a map.
// It is a mapping of Board.board to GameState.
class GameStates
{
public:
    map<vector<vector<char>>, GameState> gamestates;
};

#endif