//
// Created by boris on 3/4/21.
//
#include "Game.h"

map<string, Ship> createShips(map<string, vector<string>> fileConfiguration) {
    map<string, Ship> mapToReturn;
    for (const auto& pair : fileConfiguration) {
        if (pair.first != "Board"){
            mapToReturn.insert({pair.first, Ship(pair.first, stoi(pair.second[0]))});
        }
    }
    return mapToReturn;
}

Board createBoard(map<string, vector<string>> fileConfiguration) {
    int length = stoi(fileConfiguration.find("Board")->second[0]);
    int height = stoi(fileConfiguration.find("Board")->second[1]);
    return Board(length, height, createShips(fileConfiguration));
}

Game::Game(map<string, vector<string>> fileConfiguration) :
playerOneBoard(createBoard(fileConfiguration)),
playerTwoBoard(createBoard(fileConfiguration)){}

void Game::initialiseShips(int gameType) {
    if (gameType == 1) {
        cout << "Set up game for Single player" << endl; //TODO Implement auto placement
    } else {
        playerOneBoard.setPopulatedPoints();
    }
}

void Game::startGame(vector<int> userConfiguration) {
    initialiseShips(userConfiguration[0]); //TODO Implement auto placement for Single Player

}


//int length = stoi(fileConfiguration.find("Board")->second[0]);
//int height = stoi(fileConfiguration.find("Board")->second[1]);
//fileConfiguration.erase("Board");
//
//vector<Ship> ships;
//for (const pair<string, vector<string>>& pair : fileConfiguration) {
//int shipLength = stoi(pair.second[1]);
//Ship shipToInsert(pair.second[0], shipLength);
//ships.push_back(shipToInsert);
//cout << pair.first << endl;
//}
//
//playerOneBoard = Board(length, height, ships);
//playerTwoBoard = Board(length, height, ships);