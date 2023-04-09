#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <stack>
#include "Board.h"
#include "Game.h"
#include "GameState.h"

using namespace std;

void push_vector_stack(stack<int>& stack_ptr, vector<int> vector_val){
    for (int i {0}; i <= vector_val.size(); i ++){
        stack_ptr.push(vector_val[i]);
    }
};

void backtrack_game(){

};

int main(){
    // Opt for breadth or depth first search?
    Board my_board;
    GameStates game_states{};
    Game my_game(my_board, game_states);

    // All possible columns to place a token
    vector <int> to_place {0, 1, 2, 3, 4, 5, 6};
    // Stack used for DFS
    stack<int> dfs_stack;
    // Record of columns tokens were placed in allow back-tracking
    vector <int> column_record;

    push_vector_stack(dfs_stack, to_place);


    return 0;
}