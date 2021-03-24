////
//// Created by boris on 3/4/21.
////
//
//#include "Point.h"

#include "Game/Ship/Ship.h"
#include "Point.h"


Point::Point(pair<int, int> coordinates, shared_ptr<Ship> ship): coordinates_(coordinates), ship_(ship) {
}

const pair<int, int> &Point::getCoordinates() const {
    return coordinates_;
}

shared_ptr<Ship> Point::getShip() const {
    return ship_;
}
