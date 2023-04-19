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
#include "json.hpp"
#include "Board.h"

using namespace std;
using json = nlohmann::json;

class GameState{
    // Snapshot of a game a particular time.
    public:
        int player_turn;
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

    GameState(int player_turn_val)
    : player_turn{player_turn_val}{};
};


class GameStates{
    public:
        // mapping of board to GameState
        map <vector <vector <int>>, GameState> gamestates;

        // remove places a token can't be placed
        void add_placement_options(Board& board_ref){
            for (int i {0}; i <= 6; i++){
                if (board_ref.board[i][5] == -1){
                    this->gamestates.at(board_ref.board).to_try.push_back(i);
                };
            };
        };

        // Writes all results in a JSON format.
        void to_json(){
            json total_output;

            for (auto const& [key, val] : this->gamestates){
                string board_string = "";
                for (int i {0}; i <= 6; i++){
                    for (int j {0}; j <= 5; j++){
                        //cout << to_string(key[i][j]) << endl;
                        board_string += to_string(key[i][j]);
                    };
                };
                cout << board_string << endl; // string (key)

                total_output[board_string] = 
                        {{{"wins", val.wins.at(0)},
                            {"draws", val.draws.at(0)},
                            {"losses", val.losses.at(0)}},
                        {{"wins", val.wins.at(1)},
                            {"draws", val.draws.at(1)},
                            {"losses", val.losses.at(1)}},
                        {{"wins", val.wins.at(2)},
                            {"draws", val.draws.at(2)},
                            {"losses", val.losses.at(2)}},
                        {{"wins", val.wins.at(3)},
                            {"draws", val.draws.at(3)},
                            {"losses", val.losses.at(3)}},
                        {{"wins", val.wins.at(4)},
                            {"draws", val.draws.at(4)},
                            {"losses", val.losses.at(4)}},
                        {{"wins", val.wins.at(5)},
                            {"draws", val.draws.at(5)},
                            {"losses", val.losses.at(5)}},
                        {{"wins", val.wins.at(6)},
                            {"draws", val.draws.at(6)},
                            {"losses", val.losses.at(6)}}};

            };
            ofstream file("key.json");
            file << setw(1) << total_output << endl;
        };
};

#endif