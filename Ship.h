#ifndef SHIP_H
#define SHIP_H

#include <iostream>
using namespace std;

class Ship {
  private:
    string name_;
    int length_;
    int health;

  public:
    void setHealth(int newHealth);
    int getHealth();

    Ship (string name, int length);


};
#endif