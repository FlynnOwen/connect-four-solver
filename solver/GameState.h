// These are import gaurds
#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_
#include <string>
#include <iostream>
#include <vector>
#include "Board.h"

using namespace std;

class GameState{
    // Snapshot of a game a particular time.
    public:
        Board board;

        int player_turn;
        int wins {0};
        int losses {0};
        int draws {0};
        bool solved;
};


class GameStates{
    vector <GameState> gamestates;

    // Writes all results in a JSON format.
    void write_results();
};

#endif