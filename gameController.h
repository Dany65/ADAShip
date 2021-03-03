#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H
#endif
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class gameController
{
private:
  gameController(const map<string, vector<string>>);
	
  static gameController* inst_;

protected:
  map<string, vector<string>> configurationData_;


public:
  static gameController *getInstance(const map<string, vector<string>> configurationData); 
};