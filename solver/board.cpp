#include <iostream>
#include <string>
#include <vector>
#include "Board.h"

using namespace std;

int main(){
    Board my_board;

    vector <int> out {my_board.place_token(1, 3)};
    cout << my_board.board[3][0] << endl;
    cout << out[0] << endl;
    cout << out[1] << endl;
}