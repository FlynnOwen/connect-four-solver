#ifndef _INPUTLOADER_H_
#define _INPUTLOADER_H_

#include <string>
#include <iostream>
#include <map>

using namespace std;

class InputArgs{
    public:
        char ai_token;
        bool trash_talk;
        int difficulty;

    InputArgs(char ai_token_val,
              bool trash_talk_val,
              int difficulty_val)
    : ai_token{ai_token_val},
      trash_talk{trash_talk_val},
      difficulty{difficulty_val}{};
};

InputArgs load_inputs(){
    // AI starts first with arg 'X', human with arg 'O'
    char turn_input;
    cout << "Would you like to take the first turn? y/n" << endl;
    cin >> turn_input;

    char ai_token;
    if (turn_input == 'y'){
        ai_token = 'O';
    } else {
        ai_token = 'X';
    };
    
    // Option for the AI to trash talk
    char trash_talk_input;
    cout << "Would you like the bot to trash talk? y/n" << endl;
    cin >> trash_talk_input;

    char trash_talk;
    if (trash_talk_input == 'y'){
        trash_talk = true;
    } else {
        trash_talk = false;
    };

    // Option for the AI to trash talk
    char difficulty_input;
    cout << "Select a difficulty level 1 - 5: " << endl;
    cin >> difficulty_input;
    map<char, int> difficulty_mapping {{'1', 1000},
                                       {'2', 2500},
                                       {'3', 5000},
                                       {'4', 10000},
                                       {'5', 15000}};
    int difficulty {difficulty_mapping.at(difficulty_input)};

    return InputArgs(ai_token, trash_talk, difficulty);

};

#endif