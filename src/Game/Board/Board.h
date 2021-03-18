//
// Created by boris on 3/4/21.
//

#ifndef ADASHIP_BOARD_H
#define ADASHIP_BOARD_H

#include <iostream>
#include <vector>
#include <map>
#include "Game/Point/Point.h"

using namespace std;

class Board {
private:
//    vector<Point> listOfShotPoints; //TODO: might not be needed
//    vector<Point> populatedPoints;

    vector<vector<char>> shotsDisplay;
    vector<vector<char>> shipsDisplay;

    int length_;
    int height_;
    map<string, Ship> ships_;

public:
    Board(int length, int height, map<string, Ship> ships);
    vector<vector<char>> createShipsDisplay(int length, int height);
    vector<vector<char>> createShotsDisplay(int length, int height);

//    vector<Point> populatePoints(int length, int height, map<string, Ship> ships);

    pair<pair<string, int>, char> splitInstructions(string instructions);
    void display(vector<vector<char>>);
private:
//    bool canBePlaced()
    bool isCorrectlyFormatted(string instructions); // move to private
//    pair<string, int> splitInstructions(string instructions);

//    vector<Point> placeShips(vector<Ship> shipsToPlace);
    string returnMatch(string stingToUse, string regexToFind) const;

    pair<pair<string, int>, char> getPlacementInstructions();
};


#endif //ADASHIP_BOARD_H
