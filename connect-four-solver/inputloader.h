#ifndef _INPUTLOADER_H_
#define _INPUTLOADER_H_

#include <string>
#include <iostream>
#include <map>

using std::cout;
using std::cin;
using std::map;
using std::endl;


// Formatted arguments to be used in the main function (main.cpp).
class InputArgs
{

public:
    char ai_token;
    bool trash_talk;
    int difficulty;

    InputArgs(){
        load_inputs();
        };

    void load_inputs(){

    char turn_input;
    cout << "Would you like to take the first turn? y/n" << endl;
    cin >> turn_input;

    if (turn_input == 'y')
    {
        ai_token = 'O';
    }
    else
    {
        ai_token = 'X';
    };

    // Option for the AI to trash talk
    char trash_talk_input;
    cout << "Would you like the bot to trash talk? y/n" << endl;
    cin >> trash_talk_input;

    if (trash_talk_input == 'y')
    {
        trash_talk = true;
    }
    else
    {
        trash_talk = false;
    };

    // Difficulty of bot - more difficult means more games played during
    // simulation step.
    char difficulty_input;
    cout << "Select a difficulty level 1 - 5: " << endl;
    cin >> difficulty_input;
    map<char, int> difficulty_mapping{{'1', 500},
                                      {'2', 1500},
                                      {'3', 5000},
                                      {'4', 10000},
                                      {'5', 15000}};
    difficulty = difficulty_mapping.at(difficulty_input);
    };
};

#endif