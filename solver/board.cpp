#include <iostream>
#include <string>
#include <vector>
#include "Board.h"

using namespace std;

int main(){
    Board my_board;

    my_board.place_token(1, 3);
    cout << my_board.board[3][0] << endl;
}