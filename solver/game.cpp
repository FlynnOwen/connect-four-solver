#include <iostream>
#include <string>
#include <vector>
#include "Board.h"
#include "Game.h"
#include "GameState.h"

using namespace std;

void print_board(Board board){
    for (int i {0}; i <= 6; i++){
        for (int j {0}; j <= 5; j++){
            cout << board.board[i][j];
        };
        cout << endl;
    };
    cout << endl;
};

int main(){
    Board my_board;
    GameStates game_states{};
    Game my_game(my_board, game_states);

    my_game.place_token(4);
    print_board(my_game.board);
    my_game.write_game_state();

    my_game.place_token(4);
    print_board(my_game.board);
    my_game.check_game_state();

    my_game.write_game_state();
    my_game.check_game_state();

    cout << game_states.gamestates.size() << endl;
}