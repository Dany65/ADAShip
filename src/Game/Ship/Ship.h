#ifndef ADASHIP_SHIP_H
#define ADASHIP_SHIP_H

#include <iostream>
using namespace std;

class Ship {
  private:
    string name_;
    int length_;
    int health_; //isThisNeeded

  public:
    void setHealth(int newHealth);
    const int getHealth() const;

    const string &getName() const;

    const int getLength() const;

    Ship (string name, int length);


};
#endif