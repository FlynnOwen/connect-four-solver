// These are import gaurds
#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "Board.h"

using namespace std;

class GameState{
    // Snapshot of a game a particular time.
    public:
        int player_turn;
        int wins {0};
        int losses {0};
        int draws {0};
        bool solved;

    GameState(int player_turn_val, 
              int wins_val, 
              int losses_val, 
              int draws_val, 
              bool solved_val)
    : player_turn{player_turn_val},
    wins{wins_val},
    losses{losses_val},
    draws{draws_val},
    solved{solved_val}{};

};


class GameStates{
    public:
        // mapping of board to GameState
        map <vector <vector <int>>, GameState> gamestates;

        // Writes all results in a JSON format.
        void write_results();
};

#endif