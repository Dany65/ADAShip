////
//// Created by boris on 3/4/21.
////
//
//#include "Point.h"

#include "Game/Ship/Ship.h"
#include "Point.h"


Point::Point(pair<string, int> coordinates, Ship *ship): coordinates_(coordinates), ship_(ship) {
    cout << "Point created at: " << coordinates.first << coordinates.second << ". populated by " << ship->getName() << endl;
}

