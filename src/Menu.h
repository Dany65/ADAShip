//
// Created by boris on 3/4/21.
//

#ifndef ADASHIP_MENU_H
#define ADASHIP_MENU_H

#include <iostream>
#include <vector>

using namespace std;

class Menu {
public:
    static vector<int> gameSetUpSequence();

private:
    static bool isValidInput(const string &input);

    static int getGameType();

    static int getGameMode();
};


#endif //ADASHIP_MENU_H
