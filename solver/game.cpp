#include <iostream>
#include <string>
#include <vector>
#include "Board.h"
#include "Game.h"

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
    Game my_game(my_board);

    int player {1};
    my_game.place_token(player, 4);
    print_board(my_game.board);
}