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

void undo_move(stack<int>& column_record_ref, Game& game_ref){
    // Removes a token from a board
    int column {column_record_ref.top()};
    int row {5};
    column_record_ref.pop();

    while (game_ref.board.board[column][row] == -1){
        row -= 1;
    };
    
    game_ref.board.board[column][row] = -1;
    game_ref.player_turn = abs(game_ref.player_turn - 1);
};

void back_propogate(char result, 
                    Game& game_ref,
                    stack<int> column_record,
                    Board board){

    // undo all moves and update gamestate with the result at each undo.
    while (column_record.size() > 0){
        int i = column_record.top();
        int j = 5;

        column_record.pop();
        while (board.board[i][j] == -1){
            j--;
        };
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
#endif