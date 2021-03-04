#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class gameController
{
private:
  bool isSinglePlayer;
  bool isNormalMode;
  bool allShipsPlaced;
  bool isGameOver;

  gameController(const map<string, vector<string>>);
	

  static gameController* inst_;

protected:
  map<string, vector<string>> configurationData_;


public:
  static gameController *getInstance(const map<string, vector<string>> configurationData);
  void setToSinglePlayer();
  void setToMultiPlayer();

  void setToNormalMode();
  void setToSalvoMode();

  


};
#endif