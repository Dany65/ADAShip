//
// Created by boris on 3/4/21.
//

#ifndef ADASHIP_POINT_H
#define ADASHIP_POINT_H



#include <iostream>
#include <memory>

using namespace std;

class Point {
private:
    pair<int, int> coordinates_; // might not be needed
    shared_ptr<Ship> ship_; // might not be needed
public:
    Point(pair<int, int> coordinates, shared_ptr<Ship> ship);
    bool isPopulated();

    const pair<int, int> &getCoordinates() const;

    shared_ptr<Ship> getShip() const;
};


#endif //ADASHIP_POINT_H
