#ifndef _SIMUTILS_H_
#define _SIMUTILS_H_
#include <string>
#include <iostream>
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

void undo_move(int column, vector<vector<int>>& board_ref){
    // Removes a token from a board
    int row {5};

    while (board_ref[column][row] == -1){
        row -= 1;
    }
    cout << row << endl;
    cout << column << endl;
    board_ref[column][row] = -1;
};

void back_propogate(char result, 
                    Game& game_ref,
                    Board board){
    // undo all moves and update gamestate with the result at each undo.
    while (true){
        for (int i {0}; i <=6; i++){
            for (int j {0}; j <=5; j++){
                if (board.board[i][j] != -1){
                    board.board[i][j] = -1;
                        switch (result){
                            case 'w':
                                game_ref.gamestates.gamestates.at(board.board).wins.at(i) += 1;
                                break;
                            case 'd':
                                game_ref.gamestates.gamestates.at(board.board).draws.at(i) += 1;
                                break;
                            case 'l':
                                game_ref.gamestates.gamestates.at(board.board).losses.at(i) += 1;
                                break;
                    };
                };
            };
        };
    };
    print_board(game_ref.board);
};

#endif