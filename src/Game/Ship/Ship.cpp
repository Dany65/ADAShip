#include "Ship.h"

#include <iostream>

using namespace std;

Ship::Ship(string name, int length) : name_(name), length_(length), health_(length) {
}

void Ship::setHealth(int newHealth) {
  health_ = newHealth;
}

const int Ship::getHealth() const {
  return health_;
}

const string &Ship::getName() const {
    return name_;
}

const int Ship::getLength() const {
    return length_;
}
