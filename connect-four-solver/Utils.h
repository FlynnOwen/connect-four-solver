#ifndef _UTILS_H_
#define _UTILS_H_
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <random>
#include "Board.h"
#include "Game.h"
#include "GameState.h"

#define RESET "\033[0m"
#define YELLOW "\033[33m"
#define RED "\033[31m"

using namespace std;

// Clears the terminal, and prints the current board config with
// different colours for each token.
void print_board(Board board)
{
    system("clear");
    cout << " 0 1 2 3 4 5 6  " << endl;
    cout << "---------------" << endl;
    for (int i{0}; i <= 5; i++)
    {
        cout << '|';
        for (int j{0}; j <= 6; j++)
        {
            if (board.board[i][j] == 'O')
            {
                cout << YELLOW << board.board[i][j] << RESET;
            }
            else
            {
                cout << RED << board.board[i][j] << RESET;
            };
            cout << "|";
        };
        cout << endl;
        cout << "---------------" << endl;
    };
    cout << " 0 1 2 3 4 5 6  " << endl;
    cout << endl;
};

// Returns a set of columns that aren't already filled with tokens.
set<int> check_placement_options(Board &board_ref)
{
    set<int> options;

    for (int j{0}; j <= 6; j++)
    {
        if (board_ref.board[0][j] == ' ')
        {
            options.insert(j);
        };
    };

    return options;
};

// Prints a random line of trashtalk to the stdout.
void generate_trash_talk()
{
    random_device rd;
    mt19937 rng{rd()};
    set<string> trash_talk_options{{"AI: 'You call that a move?!'"},
                                   {"AI: 'Have actually played Connect 4 before?'"},
                                   {"AI: 'How does it feel getting outplayed by a bot?'"},
                                   {"AI: 'I don't have a grandma, but if I did, she would play better than you.'"},
                                   {"AI: 'Did you place that last token in the wrong column? Oh you didn't? Could've fooled me.'"},
                                   {"AI: 'Just give up already!'"},
                                   {"AI: 'It's over. Just concede.'"},
                                   {"AI: 'There's the option of playing with a difficulty of 1... Maybe give that a go.'"},
                                   {"AI: 'You'll never get 4 in a row. Just 4feit. (See what I did there?)'"},
                                   {"AI: 'There are easier games than this you know? Maybe try connect 2 or connect 3.'"},
                                   {"AI: 'How does it feel knowing a bot is smarter than you?'"}};

    vector<string> trash_talk_output;
    sample(trash_talk_options.begin(), trash_talk_options.end(), back_inserter(trash_talk_output), 1, rng);
    cout << trash_talk_output[0] << endl;
};
#endif