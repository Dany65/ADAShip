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

public:
    const list <Point> &getPopulatedPoints() const;

    void setShotsDisplay(const vector<vector<char>> &shotsDisplay);

    void setShipsDisplay(const vector<vector<char>> &shipsDisplay);

    void setPopulatedPointsRandomly();

    void setPopulatedPoints();

    void shoot(pair<string, int> coordinatesToShoot);

    Board(int length, int height, map<string, shared_ptr<Ship>> ships);

    int getLength() const;

    int getHeight() const;

    const map<string, shared_ptr<Ship>> &getShips() const;

    list<Point> returnPointsToPopulate();

    pair<pair<string, int>, char> splitInstructions(string instructions);

    void recordShot(pair<string, int> coordinates, char symbol);

    const vector<vector<char>> &getShotsDisplay() const;

    const vector<vector<char>> &getShipsDisplay() const;

    void display(vector<vector<char>> toDisplay);

    bool isAHit(pair<string, int> coordinates);

private:
    int length_;
    int height_;
    map<string, shared_ptr<Ship>> ships_;
    static string returnMatch(string stingToUse, string regexToFind) ;

    pair<pair<string, int>, char> getPlacementInstructions();

    bool shipCanBePlaced(int length, int height, pair<pair<string, int>, char> placementInstructions, int shipLength,
                         list <Point> takenUpPositions);

    bool willOverlapAnotherShip(pair<pair<string, int>, char> placementInstructions, int shipLength, list <Point> takenUpPoints);

    void placeShip(pair<pair<string, int>, char> placementInstruction, shared_ptr<Ship> ship, list <Point> *populatedPoints);

    void updateShipsDisplay(list <Point> populatedPoints);

    vector<vector<char>> shotsDisplay;
    vector<vector<char>> shipsDisplay;
    list<Point> populatedPoints = {};
};


#endif //ADASHIP_BOARD_H
