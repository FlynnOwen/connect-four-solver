// These are import gaurds
#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stack>
#include <fstream>
#include "Board.h"

using namespace std;

class GameState{
    // Snapshot of a game a particular time.
    public:
        char player_turn;
        // count of wins, draws and losses per possible column.
        map<int, int> wins {{0, 0}, 
                            {1 ,0},
                            {2, 0},
                            {3 ,0},
                            {4, 0},
                            {5, 0},
                            {6 ,0}};
        map<int, int> draws {{0, 0}, 
                             {1 ,0},
                             {2, 0},
                             {3 ,0},
                             {4, 0},
                             {5, 0},
                             {6 ,0}};
        map<int, int> losses {{0, 0}, 
                              {1 ,0},
                              {2, 0},
                              {3 ,0},
                              {4, 0},
                              {5, 0},
                              {6 ,0}};
        vector<int> to_try;

    GameState(char player_turn_val)
    : player_turn{player_turn_val}{};
};


class GameStates{
    public:
        // mapping of board to GameState
        map <vector <vector <char>>, GameState> gamestates;

        // remove places a token can't be placed
        void add_placement_options(Board& board_ref){
            for (int i {0}; i <= 6; i++){
                if (board_ref.board[i][5] == ' '){
                    this->gamestates.at(board_ref.board).to_try.push_back(i);
                };
            };
        };
};

#endif