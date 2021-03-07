////
//// Created by boris on 3/4/21.
////
//#include "Game.h"
//
//
//Game::Game(vector<int> userConfiguration, map<string, vector<string>> fileConfiguration) {
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
//    playerOneBoard = Board(length, height, ships);
//    playerTwoBoard = Board(length, height, ships);
//}
