// These are import gaurds
#ifndef _BOARD_H_
#define _BOARD_H_
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Board{
    public:
        vector <vector <int>> board;

        void place_token(int player, int column);
};

#endif