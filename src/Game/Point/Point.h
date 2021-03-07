//
// Created by boris on 3/4/21.
//

#ifndef ADASHIP_POINT_H
#define ADASHIP_POINT_H



#include <iostream>

using namespace std;

class Point {
private:
    pair<string, int> coordinates_; // might not be needed
    Ship* ship_; // might not be needed
    bool populated_; // set to true when ship is placed
public:
    Point(pair<string, int> coordinates, Ship* ship);
    bool isPopulated();
};


#endif //ADASHIP_POINT_H
