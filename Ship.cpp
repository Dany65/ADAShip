#include <iostream>

using namespace std;

#include "Ship.h"

#include <iostream>

void Ship::setHealth(int newHealth) {
  health = newHealth;
}

int Ship::getHealth()  {
  return health;
}

Ship::Ship(string name, int length) : name_(name), length_(length) {
  setHealth(length);
  cout << "ship " << name << " with length " << length << " abd health of " << getHealth() << endl;
  }