//
// Created by boris on 3/4/21.
//
#include <regex>
#include <algorithm>
#include<cmath>

#include "Game.h"

map<string, shared_ptr<Ship>> createShips(map<string, vector<string>> fileConfiguration) {
    map<string, shared_ptr<Ship>> mapToReturn;
    for (const auto &pair : fileConfiguration) {
        if (pair.first != "Board") {
            mapToReturn.insert({pair.first, make_shared<Ship>(pair.first, stoi(pair.second[0]))});
        }
    }
    return mapToReturn;
}

Board createBoard(map<string, vector<string>> fileConfiguration) {
    int length = stoi(fileConfiguration.find("Board")->second[0]);
    int height = stoi(fileConfiguration.find("Board")->second[1]);
    return Board(length, height, createShips(fileConfiguration));
}

string returnMatch(string stringToUse, string regexToFind) {
    smatch match;
    regex_search(stringToUse, match, std::regex(regexToFind));
    return match.str();
}

int numberFromExcelColumnn(string column) {
    int retVal = 0;
    for (int iChar = column.length() - 1; iChar >= 0; iChar--) {
        char colPiece = column[iChar];
        int colNum = colPiece - 64;
        retVal = retVal + colNum * (int) pow(26, column.length() - (iChar + 1));
    }
    return retVal;
}

bool allShipsSunk(Board *board) {
    for (const auto &shipKeyValue : board->getShips()) {
        if (shipKeyValue.second->getHealth() > 0) {
            return false;
        }
    }
    return true;
}

pair<string, int> letPlayerShoot(int length, int height, list<pair<string, int>> shotPoints) {
    while (true) {
        cout << "Pick a spot on the map to attemptToSink: example A3" << endl;
        string pointToShoot;
        getline(cin, pointToShoot);
        bool correctFormat = std::regex_match(pointToShoot,
                                              std::regex("^[A-Za-z]{1,}[1-9]{1,}$")); // checkingFormatting of input

        if (correctFormat) {
            //splitting instructions
            string letterCoordinates = returnMatch(pointToShoot, "^[A-Za-z]{1,}");
            std::transform(letterCoordinates.begin(), letterCoordinates.end(), letterCoordinates.begin(), ::toupper);
            string numberCoordinate = pointToShoot.substr(letterCoordinates.length());


            if (length >= numberFromExcelColumnn(letterCoordinates) &&
                height >= stoi(numberCoordinate)) { // checks  shot is on the map
                bool pointAlreadyShot = false;
                for (pair<string, int> point : shotPoints) {
                    if (point.first == letterCoordinates && point.second == stoi(numberCoordinate)) {
                        cout << "Point is already shot" << endl;
                        pointAlreadyShot = true;
                    }
                } // checked if the point has been shot already

                if (!pointAlreadyShot) { // if point has not been shot, return, otherwise make user pick a new opint
                    return pair(letterCoordinates, stoi(numberCoordinate));
                }

            } else {
                cout << "Shot is out of map, try again" << endl;
            }
        } else {
            cout << "Follow the specified format" << endl;
        }
    }
}

Game::Game(map<string, vector<string>> fileConfiguration) :
        playerOneBoard(createBoard(fileConfiguration)),
        playerTwoBoard(createBoard(fileConfiguration)) {}

void Game::initialiseShips(int gameType) {
    if (gameType == 1) {
        cout << "Set up game for Single player" << endl; //TODO Implement auto placement
        playerOneBoard.setPopulatedPoints(); // TODO implement pause between placement
        playerTwoBoard.setPopulatedPointsRandomly();
    } else {
        playerOneBoard.setPopulatedPoints(); // TODO implement pause between placement
        playerTwoBoard.setPopulatedPoints();
    }
}

void Game::startGame(vector<int> userConfiguration) {
    initialiseShips(userConfiguration[0]); //TODO Implement auto placement for Single Player Mode
    beginShootingSequence(userConfiguration); //TODO implement Salvo Mode
}

void Game::beginShootingSequence(vector<int> userConfiguration) {
    if (userConfiguration[1] == 1) {
        normalShooterGame(userConfiguration);
    } else if (userConfiguration[1] == 2) {
        salvoShooterGame(userConfiguration);
    }
//    else {
//        minesGame();
//    }
}

void Game::normalShooterGame(vector<int> userConfiguration) {
    cout << "ENTERED normal game" << endl;

    int boardLength = playerOneBoard.getLength();
    int boardHeight = playerOneBoard.getHeight();
    list<pair<string, int>> pointsShotByPlayerOne;
    list<pair<string, int>> pointsShotByPlayerTwo;

    bool playerOnesTurn = true;
    while (true) {
        //picking game mode


        if (allShipsSunk(&playerTwoBoard)) { // checks if player one has won
            cout << "Player One Won!" << endl;
            break;
        }
        if (allShipsSunk(&playerOneBoard)) { // checks if player tow has won
            cout << "Player Two Won!" << endl;
            break;
        }


        if (playerOnesTurn) { // TODO implement salvo here. use userConfiguration to do this
            cout << "Player one's turn" << endl;
            playerOneBoard.display(playerOneBoard.getShotsDisplay());
            pair<string, int> shotPoint = letPlayerShoot(boardLength, boardHeight, pointsShotByPlayerOne);

            if (playerTwoBoard.isAHit(shotPoint)) { // deciding how to update the shotsDisplay for the player
                pair<bool, string> shipWasSunk = playerTwoBoard.attemptToSink(shotPoint);
                if (shipWasSunk.first) {  // displaying ship as sunk to let player know
                    playerOneBoard.displayShipAsSunk(shipWasSunk.second, playerTwoBoard.getPopulatedPoints());
                } else { // showing a ship was hit to the player
                    playerOneBoard.recordShot(shotPoint, 'X');
                }
            } else {
                playerOneBoard.recordShot(shotPoint, '*');
            }


            pointsShotByPlayerOne.push_back(shotPoint);

            playerOnesTurn = false;
        } else {
            if (userConfiguration[0] == 1) { // TODO implement AI
                cout << "AI SHOULD PLAY HERE" << endl;
            } else {
                cout << "Player two's turn" << endl;
                playerTwoBoard.display(playerTwoBoard.getShotsDisplay());
                pair<string, int> shotPoint = letPlayerShoot(boardLength, boardHeight, pointsShotByPlayerTwo);
                pointsShotByPlayerTwo.push_back(shotPoint);

                if (playerOneBoard.isAHit(shotPoint)) { // deciding how to update the shotsDisplay for the player
                    pair<bool, string> shipWasSunk = playerOneBoard.attemptToSink(shotPoint);
                    if (shipWasSunk.first) {  // displaying ship as sunk to let player know
                        playerTwoBoard.displayShipAsSunk(shipWasSunk.second, playerOneBoard.getPopulatedPoints());

                    } else { // showing a ship was hit to the player
                        playerTwoBoard.recordShot(shotPoint, 'X');
                    }
                } else {
                    playerTwoBoard.recordShot(shotPoint, '*');
                }

            }
            playerOnesTurn = true;
        }
        cout << "Game will either end on next loop or next player will play" << endl;
    }
}

void Game::salvoShooterGame(vector<int> userConfiguration) {
    cout << "ENTERED salvo game" << endl;

    int boardLength = playerOneBoard.getLength();
    int boardHeight = playerOneBoard.getHeight();
    list<pair<string, int>> pointsShotByPlayerOne;
    list<pair<string, int>> pointsShotByPlayerTwo;

    bool playerOnesTurn = true;
    while (true) {

        if (allShipsSunk(&playerTwoBoard)) { // checks if player one has won
            cout << "Player One Won!" << endl;
            break;
        }
        if (allShipsSunk(&playerOneBoard)) { // checks if player tow has won
            cout << "Player Two Won!" << endl;
            break;
        }


        if (playerOnesTurn) {
            cout << "Player one's turn:" << endl;
            playerOneBoard.display(playerOneBoard.getShotsDisplay());
            cout << "You have to take " << playerOneBoard.countAliveShips() << " shots." << endl;
            for (int i = 0; i < playerOneBoard.countAliveShips(); ++i) {

                pair<string, int> shotPoint = letPlayerShoot(boardLength, boardHeight, pointsShotByPlayerOne);

                if (playerTwoBoard.isAHit(shotPoint)) { // deciding how to update the shotsDisplay for the player
                    pair<bool, string> shipWasSunk = playerTwoBoard.attemptToSink(shotPoint);
                    if (shipWasSunk.first) {  // displaying ship as sunk to let player know
                        playerOneBoard.displayShipAsSunk(shipWasSunk.second, playerTwoBoard.getPopulatedPoints());
                    } else { // showing a ship was hit to the player
                        playerOneBoard.recordShot(shotPoint, 'X');
                    }
                } else {
                    playerOneBoard.recordShot(shotPoint, '*');
                }


                pointsShotByPlayerOne.push_back(shotPoint);
            }

            playerOnesTurn = false;
        } else {
            if (userConfiguration[0] == 1) { // TODO implement AI
                cout << "AI SHOULD PLAY HERE" << endl;
            } else {
                cout << "Player two's turn" << endl;
                playerTwoBoard.display(playerTwoBoard.getShotsDisplay());
                cout << "You have to take " << playerTwoBoard.countAliveShips() << " shots." << endl;
                for (int i = 0; i < playerTwoBoard.countAliveShips(); ++i) {

                    pair<string, int> shotPoint = letPlayerShoot(boardLength, boardHeight, pointsShotByPlayerTwo);
                    pointsShotByPlayerTwo.push_back(shotPoint);

                    if (playerOneBoard.isAHit(shotPoint)) { // deciding how to update the shotsDisplay for the player
                        pair<bool, string> shipWasSunk = playerOneBoard.attemptToSink(shotPoint);
                        if (shipWasSunk.first) {  // displaying ship as sunk to let player know
                            playerTwoBoard.displayShipAsSunk(shipWasSunk.second, playerOneBoard.getPopulatedPoints());

                        } else { // showing a ship was hit to the player
                            playerTwoBoard.recordShot(shotPoint, 'X');
                        }
                    } else {
                        playerTwoBoard.recordShot(shotPoint, '*');
                    }

                }
            }
            playerOnesTurn = true;
        }
        cout << "Game will either end on next loop or next player will play" << endl;
    }
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