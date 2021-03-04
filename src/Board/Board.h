//
// Created by boris on 3/4/21.
//

#ifndef ADASHIP_BOARD_H
#define ADASHIP_BOARD_H

#include <iostream>
#include <vector>
#include "Ship/Ship.h"

using namespace std;

class Board {
private:
    vector<vector<string>> board;
public:
    Board(int length, int height, vector<Ship> hips);

};


#endif //ADASHIP_BOARD_H
