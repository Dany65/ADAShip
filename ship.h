#ifndef SHIP_H
#define SHIP_H
#endif
#include <iostream>
using namespace std;

class ship
{
public:
  ship(string name, int length);

private:
  vector<pair<string, string>> coordinates;
};
