#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_
#include <vector>
#include <map>
#include <string>
#include "Board.h"

using namespace std;

class GameState{
    // Snapshot of a game a particular time.
    public:
        char player_turn;
        // count of wins, draws and losses per possible column.
        vector<int> wins {0, 0, 0, 0, 0, 0, 0};
        vector<int> draws {0, 0, 0, 0, 0, 0, 0};
        vector<int> losses {0, 0, 0, 0, 0, 0, 0};

    GameState(char player_turn_val)
    : player_turn{player_turn_val}{};
};


class GameStates{
    public:
        // mapping of board to GameState
        map <vector <vector <char>>, GameState> gamestates;
};

#endif