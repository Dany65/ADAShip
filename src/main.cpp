#include <iostream>
#include <map>
#include <vector>
#include "Game/Game.h"
#include "Game/Ship/Ship.h"
#include "Game/Point/Point.h"
#include "Game/Board/Board.h"

#include "configurationReader/ConfigurationReader.h"
#include "Menu.h"


using namespace std;



int main() {
    vector<int> userConfiguration =  Menu::gameSetUpSequence();
    map<string, vector<string>> fileConfiguration = ConfigurationReader::getConfiguration();
//    cout << fileConfiguration.find("Board")->second[0] << ", " << fileConfiguration.find("Board")->second[1] << endl << endl << endl << endl;
//    createShips(fileConfiguration);
//    int length = stoi(fileConfiguration.find("Board")->first);
//    int height = stoi(fileConfiguration.find("Board")->second);
//    cout << length << ", " << height << endl;
    Game game(fileConfiguration);
    game.startGame(userConfiguration);

//
//    Ship ship("Titanik", 2);
//    Ship ship2("Sail", 1);
//    map<string, Ship> ships;
//    ships.insert({ship.getName(), ship});
//    ships.insert({ship2.getName(), ship2});
//
//    Board playerOneBoard(4, 2, ships);
//    playerOneBoard.setPopulatedPoints(playerOneBoard.returnPointsToPopulate());
//
//    Board playerTwoBoard(4, 2, ships);
//    playerOneBoard.setPopulatedPoints(playerOneBoard.returnPointsToPopulate());



}