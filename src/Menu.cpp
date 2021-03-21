//
// Created by boris on 3/4/21.
//

#include "Menu.h"

vector<int> Menu::gameSetUpSequence() {
    cout << "Welcome to ADA Ship." << endl;

    int gameType;
    int gameMode;
    do {
        gameType = getGameType(); // ask to pick type
        if (gameType == 0) { // they chose to quit the game
            cout << "GoodBye";
            gameMode = -1;
        } else {
            gameMode = getGameMode(); // ask to pick mode
        }
    } while (gameMode == 0);
    return vector<int>{gameType, gameMode};
}

int Menu::getGameType() {
    bool isValid;
    string input;
    do {
        cout << endl << "MENU:" << endl;
        cout << "1. Play against the computer" << endl;
        cout << "2. Play with a friend" << endl;
        cout << "0. To Quit" << endl << endl;
        cout << "Enter 1, 2 or 0";
        getline(cin, input);
        isValid = isValidInput(input);

        if (isValid) {
            return stoi(input);
        } else {
            cout << "Invalid choice. Enter 1, 2 or 0" << endl;
        }
    } while (!isValid);
}

int Menu::getGameMode() {
    bool isValid;
    string input;
    do {
        cout << endl << "MENU:" << endl;
        cout << "1. Normal Mode" << endl;
        cout << "2. Salvo Mode" << endl;
        cout << "0. To go Back" << endl << endl;
        cout << "Enter 1, 2 or 0";
        getline(cin, input);
        isValid = isValidInput(input);

        if (isValid) {
            return stoi(input);
        } else {
            cout << "Invalid choice. Enter 1, 2 or 0" << endl;
        }
    } while (!isValid);
}

bool Menu::isValidInput(const string &input) {
    if (input.length() == 1 && isdigit(input[0]) && stoi(input) < 3 && stoi(input) > -1) {
        return true;
    }
    return false;
}
