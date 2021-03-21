//
// Created by boris on 3/4/21.
//

#ifndef ADASHIP_BOARD_H
#define ADASHIP_BOARD_H

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include "../Ship/Ship.h"
#include "../Point/Point.h"

using namespace std;

class Board {
private:
//    vector<Point> listOfShotPoints; //TODO: might not be needed

    vector<vector<char>> shotsDisplay;
    vector<vector<char>> shipsDisplay;
    list<Point> populatedPoints = {};

    int length_;
public:
    void setShotsDisplay(const vector<vector<char>> &shotsDisplay);

    void setShipsDisplay(const vector<vector<char>> &shipsDisplay);

    void setPopulatedPoints(const list <Point> &populatedPoints);

private:
    int height_;
    map<string, Ship> ships_;

public:
    Board(int length, int height, map<string, Ship> ships);

    list<Point> returnPointsToPopulate();

    pair<pair<string, int>, char> splitInstructions(string instructions);
private:
//    bool canBePlaced()
//    pair<string, int> splitInstructions(string instructions);

//    vector<Point> placeShips(vector<Ship> shipsToPlace);
    static string returnMatch(string stingToUse, string regexToFind) ;

    pair<pair<string, int>, char> getPlacementInstructions();

    bool shipCanBePlaced(int length, int height, pair<pair<string, int>, char> placementInstructions, int shipLength,
                         list <Point> takenUpPositions);

    bool willOverlapAnotherShip(pair<pair<string, int>, char> placementInstructions, int shipLength, list <Point> takenUpPoints);

    void placeShip(pair<pair<string, int>, char> placementInstruction, shared_ptr<Ship> ship, list <Point> *populatedPoints);

    void updateShipsDisplay(list <Point> populatedPoints);
};


#endif //ADASHIP_BOARD_H
