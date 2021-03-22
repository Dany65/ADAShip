#include "Ship.h"

#include <iostream>

using namespace std;

Ship::Ship(string name, int length) : name_(name), length_(length), health_(length) {
    cout << "ship " << name << " with length " << length << " and health of " << getHealth() << endl;
}

void Ship::setHealth(int newHealth) {
  health_ = newHealth;
  cout << "Ship " << name_ << " now has health of " << health_ << endl;
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
