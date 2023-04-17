#ifndef _SIMUTILS_H_
#define _SIMUTILS_H_
#include <string>
#include <iostream>
#include <vector>
#include <stack>
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

void undo_move(stack<int>& column_record_ref, Board& board_ref){
    // Removes a token from a board
    int column {column_record_ref.top()};
    int row {5};
    column_record_ref.pop();

    while (board_ref.board[column][row] == -1){
        row -= 1;
    }
    cout << row << endl;
    cout << column << endl;
    board_ref.board[column][row] = -1;
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