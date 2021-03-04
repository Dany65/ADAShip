//
// Created by boris on 3/4/21.
//

#ifndef ADASHIP_POINT_H
#define ADASHIP_POINT_H


#include <Ship/Ship.h>

class Point {
private:
    pair<string, int> coordinates; // might not be needed


    bool shot = false;
    bool populated = false; // set to true when ship is placed
    Ship* ship = nullptr; // might not be needed
public:
    bool isPopulated();


};


#endif //ADASHIP_POINT_H
