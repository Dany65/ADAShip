////
//// Created by boris on 3/5/21.
////
//#include <iostream>
//#include <map>
//#include <vector>
//#include <Game/Board/Board.h>
//#include <Game/Ship/Ship.h>
//
//#include "GameController.h"
//
//using namespace std;
//
//void GameController::initiateGame(vector<int> userConfiguration, map<string, vector<string>> fileConfiguration) {
//
//
//
//
//
//    int length = stoi(fileConfiguration.find("Board")->second[0]);
//    int height = stoi(fileConfiguration.find("Board")->second[1]);
//    fileConfiguration.erase("Board");
//
//    vector<Ship> ships;
//    for (const pair<string, vector<string>>& pair : fileConfiguration) {
//        int shipLength = stoi(pair.second[1]);
//        Ship shipToInsert(pair.second[0], shipLength);
//        ships.push_back(shipToInsert);
//        cout << pair.first << endl;
//    }
//
//    Board playerOneBoard = Board(length, height, ships);
//    Board playerTwoBoard = Board(length, height, ships);
//
//}
//
//GameController::GameController(vector<int> userConfiguration, map<string, vector<string>> fileConfiguration):
//    userConfiguration_(userConfiguration), fileConfiguration_(fileConfiguration){
//};
