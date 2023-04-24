// These are import gaurds
#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stack>
#include <set>
#include <fstream>
#include "Board.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

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

        // Writes all results in a JSON format.
        void to_json(){
            json total_output;

            for (auto const& [key, val] : this->gamestates){
                string board_string = "";
                for (int i {0}; i <= 6; i++){
                    for (int j {0}; j <= 5; j++){
                        board_string += key[i][j];
                    };
                };

                total_output[board_string] = 
                        {{{"wins", val.wins[0]},
                            {"draws", val.draws[0]},
                            {"losses", val.losses[0]}},
                        {{"wins", val.wins[1]},
                            {"draws", val.draws[1]},
                            {"losses", val.losses[1]}},
                        {{"wins", val.wins[2]},
                            {"draws", val.draws[2]},
                            {"losses", val.losses[2]}},
                        {{"wins", val.wins[3]},
                            {"draws", val.draws[3]},
                            {"losses", val.losses[3]}},
                        {{"wins", val.wins[4]},
                            {"draws", val.draws[4]},
                            {"losses", val.losses[4]}},
                        {{"wins", val.wins[5]},
                            {"draws", val.draws[5]},
                            {"losses", val.losses[5]}},
                        {{"wins", val.wins[6]},
                            {"draws", val.draws[6]},
                            {"losses", val.losses[6]}}};

            };
            ofstream file("key.json");
            file << setw(1) << total_output << endl;
        };
};

#endif