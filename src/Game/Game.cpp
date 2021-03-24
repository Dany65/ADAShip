//
// Created by boris on 3/4/21.
//
#include <regex>
#include <algorithm>
#include<cmath>
#include <cstdlib>
#include <ctime>

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

string intToLetterss(int value) {
    string result = "";
    while (--value >= 0) {
        result = (char) ('A' + value % 26) + result;
        value /= 26;
    }
    return result;
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
                                              std::regex("^[A-Za-z]{1,}[0-9]{1,}$")); // checkingFormatting of input

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


bool shotHitAMine(pair<string, int> shotPoint, list<pair<string, int>> mineLocations) {
    for (pair<string, int> mine : mineLocations) {
        if (mine.first == shotPoint.first && mine.second == shotPoint.second) {
            return true;
        }
    }
    return false;
}


Game::Game(map<string, vector<string>> fileConfiguration) :
        playerOneBoard(createBoard(fileConfiguration)),
        playerTwoBoard(createBoard(fileConfiguration)) {}

void Game::initialiseShips(int gameType) {
    if (gameType == 1) {
        cout << "Set up game for Single player" << endl;
        playerOneBoard.setPopulatedPoints(); // TODO implement pause between placement
        playerTwoBoard.setPopulatedPointsRandomly();
    } else {
        playerOneBoard.setPopulatedPoints(); // TODO implement pause between placement
        playerTwoBoard.setPopulatedPoints();
    }
}

void Game::startGame(vector<int> userConfiguration) {
    initialiseShips(userConfiguration[0]);
    beginShootingSequence(userConfiguration);
}

void Game::beginShootingSequence(vector<int> userConfiguration) {
    if (userConfiguration[1] == 1) {
        normalShooterGame(userConfiguration);
    } else if (userConfiguration[1] == 2) {
        salvoShooterGame(userConfiguration);
    } else {
        minesGame(userConfiguration);
    }
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
            cout << "Player one's turn!" << endl;
            cout << "Your field:" << endl;
            playerOneBoard.display(playerOneBoard.getShipsDisplay());

            cout << endl << endl << "Opponents field: " << endl;
            playerOneBoard.display(playerOneBoard.getShotsDisplay());

            pair<string, int> shotPoint = letPlayerShoot(boardLength, boardHeight, pointsShotByPlayerOne);
            pointsShotByPlayerOne.push_back(shotPoint);

            if (playerTwoBoard.isAHit(shotPoint)) { // if the shot is a hit
                pair<bool, string> shipWasSunk = playerTwoBoard.attemptToSink(
                        shotPoint); // see if the shot sunk the ship it hit
                if (shipWasSunk.first) {  // if it sunk the ship it hit
                    playerOneBoard.displayShipAsSunkOnShotsDisplay(shipWasSunk.second,
                                                                   playerTwoBoard.getPopulatedPoints()); // update your shots display so you know you sunk it WORKS
                    playerTwoBoard.displayShipAsSunkOnShipsDisplay(
                            shipWasSunk.second); // make player two update their ships board as that ship being sunk

                } else { // showing a ship was hit to the player
                    playerOneBoard.recordOnShotsDisplay(shotPoint, 'X');
                    playerTwoBoard.recordOnShipsDisplay(shotPoint, 'X');
                }
            } else {
                playerOneBoard.recordOnShotsDisplay(shotPoint, '*');
                playerTwoBoard.recordOnShipsDisplay(shotPoint, '*');

            }
            playerOnesTurn = false;
        } else {
            if (userConfiguration[0] == 1) { // TODO implement AI
                cout << "AI SHOULD PLAY HERE" << endl;
            } else {
                cout << "Player two's turn" << endl;

                cout << "Your field:" << endl;
                playerTwoBoard.display(playerTwoBoard.getShipsDisplay());

                cout << endl << endl << "Opponents field: " << endl;
                playerTwoBoard.display(playerTwoBoard.getShotsDisplay());

                pair<string, int> shotPoint = letPlayerShoot(boardLength, boardHeight, pointsShotByPlayerTwo);
                pointsShotByPlayerTwo.push_back(shotPoint);

                if (playerOneBoard.isAHit(shotPoint)) { // if shot was a hit
                    pair<bool, string> shipWasSunk = playerOneBoard.attemptToSink(shotPoint); //see if it sunk a ship
                    if (shipWasSunk.first) {  // shot sunk a ship
                        playerTwoBoard.displayShipAsSunkOnShotsDisplay(shipWasSunk.second,
                                                                       playerOneBoard.getPopulatedPoints()); // update your shots map show that
                        playerOneBoard.displayShipAsSunkOnShipsDisplay(
                                shipWasSunk.second); // make opponent update their ships map so they know it's sunk
                    } else { // ig the ship was not sunk
                        playerTwoBoard.recordOnShotsDisplay(shotPoint, 'X'); // update your shots map as a hit
                        playerOneBoard.recordOnShipsDisplay(shotPoint,
                                                            'X'); //make opponent update their ships map as a hit

                    }
                } else {
                    playerTwoBoard.recordOnShotsDisplay(shotPoint, '*');
                    playerOneBoard.recordOnShipsDisplay(shotPoint, '*');
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
            cout << "Player one's turn!" << endl;
            cout << "Your field:" << endl;
            playerOneBoard.display(playerOneBoard.getShipsDisplay());

            cout << endl << endl << "Opponents field: " << endl;
            playerOneBoard.display(playerOneBoard.getShotsDisplay());

            cout << endl << "You have to take " << playerOneBoard.countAliveShips() << " shots." << endl;

            for (int i = 0; i < playerOneBoard.countAliveShips(); ++i) {

                pair<string, int> shotPoint = letPlayerShoot(boardLength, boardHeight, pointsShotByPlayerOne);
                pointsShotByPlayerOne.push_back(shotPoint);

                if (playerTwoBoard.isAHit(shotPoint)) { // if the shot is a hit
                    pair<bool, string> shipWasSunk = playerTwoBoard.attemptToSink(
                            shotPoint); // see if the shot sunk the ship it hit
                    if (shipWasSunk.first) {  // if it sunk the ship it hit
                        playerOneBoard.displayShipAsSunkOnShotsDisplay(shipWasSunk.second,
                                                                       playerTwoBoard.getPopulatedPoints()); // update your shots display so you know you sunk it WORKS
                        playerTwoBoard.displayShipAsSunkOnShipsDisplay(
                                shipWasSunk.second); // make player two update their ships board as that ship being sunk

                    } else { // showing a ship was hit to the player
                        playerOneBoard.recordOnShotsDisplay(shotPoint, 'X');
                        playerTwoBoard.recordOnShipsDisplay(shotPoint, 'X');
                    }
                } else {
                    playerOneBoard.recordOnShotsDisplay(shotPoint, '*');
                    playerTwoBoard.recordOnShipsDisplay(shotPoint, '*');
                }
            }

            playerOnesTurn = false;
        } else {
            if (userConfiguration[0] == 1) { // TODO implement AI
                cout << "AI SHOULD PLAY HERE" << endl;
            } else {
                cout << "Player two's turn" << endl;

                cout << "Your field:" << endl;
                playerTwoBoard.display(playerTwoBoard.getShipsDisplay());

                cout << endl << endl << "Opponents field: " << endl;
                playerTwoBoard.display(playerTwoBoard.getShotsDisplay());

                cout << endl << "You have to take " << playerTwoBoard.countAliveShips() << " shots." << endl;
                for (int i = 0; i < playerTwoBoard.countAliveShips(); ++i) {

                    pair<string, int> shotPoint = letPlayerShoot(boardLength, boardHeight, pointsShotByPlayerTwo);
                    pointsShotByPlayerTwo.push_back(shotPoint);

                    if (playerOneBoard.isAHit(shotPoint)) { // if shot was a hit
                        pair<bool, string> shipWasSunk = playerOneBoard.attemptToSink(
                                shotPoint); //see if it sunk a ship
                        if (shipWasSunk.first) {  // shot sunk a ship
                            playerTwoBoard.displayShipAsSunkOnShotsDisplay(shipWasSunk.second,
                                                                           playerOneBoard.getPopulatedPoints()); // update your shots map show that
                            playerOneBoard.displayShipAsSunkOnShipsDisplay(
                                    shipWasSunk.second); // make opponent update their ships map so they know it's sunk
                        } else { // ig the ship was not sunk
                            playerTwoBoard.recordOnShotsDisplay(shotPoint, 'X'); // update your shots map as a hit
                            playerOneBoard.recordOnShipsDisplay(shotPoint,
                                                                'X'); //make opponent update their ships map as a hit

                        }
                    } else {
                        playerTwoBoard.recordOnShotsDisplay(shotPoint, '*');
                        playerOneBoard.recordOnShipsDisplay(shotPoint, '*');
                    }
                }
            }
            playerOnesTurn = true;
        }
        cout << "Game will either end on next loop or next player will play" << endl;
    }
}

void Game::minesGame(vector<int> userConfiguration) {
    cout << "ENTERED mines game" << endl;

    int boardLength = playerOneBoard.getLength();
    int boardHeight = playerOneBoard.getHeight();

    if (boardHeight * boardLength - playerOneBoard.getShips().size() < 5) {
        throw "The board is too small to play mines with the ships specified";
    }

    list<pair<string, int>> pointsShotByPlayerOne;
    list<pair<string, int>> pointsShotByPlayerTwo;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    list<pair<string, int>> minesForPlayerOne = generateMineLocations(playerOneBoard.getPopulatedPoints());
    for (pair<string, int> pair : minesForPlayerOne) {
        playerOneBoard.recordOnShipsDisplay(pair, 'M');
    } // records mines positions so player one can see them

    list<pair < string, int>>
    minesForPlayerTwo = generateMineLocations(playerTwoBoard.getPopulatedPoints());
    for (pair<string, int> pair : minesForPlayerTwo) {
        playerTwoBoard.recordOnShipsDisplay(pair, 'M');
    } // records mines positions so player two can see them

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
            cout << "Player one's turn!" << endl;
            cout << "Your field:" << endl;
            playerOneBoard.display(playerOneBoard.getShipsDisplay());

            cout << endl << endl << "Opponents field: " << endl;
            playerOneBoard.display(playerOneBoard.getShotsDisplay());

            pair<string, int> shotPoint = letPlayerShoot(boardLength, boardHeight, pointsShotByPlayerOne);
            pointsShotByPlayerOne.push_back(shotPoint);

            if (playerTwoBoard.isAHit(shotPoint)) { // if the shot hit a ship
                pair<bool, string> shipWasSunk = playerTwoBoard.attemptToSink(
                        shotPoint); // see if the shot sunk the ship it hit
                if (shipWasSunk.first) {  // if it sunk the ship it hit
                    playerOneBoard.displayShipAsSunkOnShotsDisplay(shipWasSunk.second,
                                                                   playerTwoBoard.getPopulatedPoints()); // update your shots display so you know you sunk it WORKS
                    playerTwoBoard.displayShipAsSunkOnShipsDisplay(
                            shipWasSunk.second); // make player two update their ships board as that ship being sunk

                } else { // showing a ship was hit to the player
                    playerOneBoard.recordOnShotsDisplay(shotPoint, 'X');
                    playerTwoBoard.recordOnShipsDisplay(shotPoint, 'X');
                }
            } else if (shotHitAMine(shotPoint, minesForPlayerTwo)) {
                playerOneBoard.recordOnShotsDisplay(shotPoint, '@');
                playerTwoBoard.recordOnShipsDisplay(shotPoint, '@');
                list<pair < string, int>>
                positionsHit = positionsHitByExplosion(shotPoint);
                for (pair<string, int> position : positionsHit) {
                    if (playerTwoBoard.isAHit(position)) { // did the explostion at this point hit a ship
                        pair<bool, string> shipWasSunk = playerTwoBoard.attemptToSink(
                                position); // see if it sunk the ship it hit
                        if (shipWasSunk.first) {  // if it sunk the ship it hit
                            playerOneBoard.displayShipAsSunkOnShotsDisplay(shipWasSunk.second,
                                                                           playerTwoBoard.getPopulatedPoints()); // update your shots display so you know you sunk it
                            playerTwoBoard.displayShipAsSunkOnShipsDisplay(
                                    shipWasSunk.second); // make player two update their ships board as that ship being sunk

                        } else { // showing a ship was hit to the player
                            playerOneBoard.recordOnShotsDisplay(position, 'X');
                            playerTwoBoard.recordOnShipsDisplay(position, 'X');
                        }
                    } else {
                        playerOneBoard.recordOnShotsDisplay(position, '*');
                        playerTwoBoard.recordOnShipsDisplay(position, '*');
                    }
                }
            } else {
                playerOneBoard.recordOnShotsDisplay(shotPoint, '*');
                playerTwoBoard.recordOnShipsDisplay(shotPoint, '*');

            }
            playerOnesTurn = false;
        } else {
            cout << "Player two's turn" << endl;

            cout << "Your field:" << endl;
            playerTwoBoard.display(playerTwoBoard.getShipsDisplay());

            cout << endl << endl << "Opponents field: " << endl;
            playerTwoBoard.display(playerTwoBoard.getShotsDisplay());

            pair<string, int> shotPoint;
            if (userConfiguration[0] == 1) { // TODO implement AI
                cout << "AI SHOULD PLAY HERE" << endl;
            } else {
                shotPoint = letPlayerShoot(boardLength, boardHeight, pointsShotByPlayerTwo);
            }
            pointsShotByPlayerTwo.push_back(shotPoint);

            if (playerOneBoard.isAHit(shotPoint)) { // if shot was a hit
                pair<bool, string> shipWasSunk = playerOneBoard.attemptToSink(shotPoint); //see if it sunk a ship
                if (shipWasSunk.first) {  // shot sunk a ship
                    playerTwoBoard.displayShipAsSunkOnShotsDisplay(shipWasSunk.second,
                                                                   playerOneBoard.getPopulatedPoints()); // update your shots map show that
                    playerOneBoard.displayShipAsSunkOnShipsDisplay(
                            shipWasSunk.second); // make opponent update their ships map so they know it's sunk
                } else { // ig the ship was not sunk
                    playerTwoBoard.recordOnShotsDisplay(shotPoint, 'X'); // update your shots map as a hit
                    playerOneBoard.recordOnShipsDisplay(shotPoint,
                                                        'X'); //make opponent update their ships map as a hit

                }
            } else if (shotHitAMine(shotPoint, minesForPlayerOne)) {
                playerTwoBoard.recordOnShotsDisplay(shotPoint, '@');
                playerOneBoard.recordOnShipsDisplay(shotPoint, '@');

                list<pair<string, int>> positionsHit = positionsHitByExplosion(shotPoint);
                for (pair<string, int> position : positionsHit) {
                    if (playerOneBoard.isAHit(position)) { // if explosion point hit a ship
                        pair<bool, string> shipWasSunk = playerOneBoard.attemptToSink(position); //see if it sunk a ship
                        if (shipWasSunk.first) {  // shot sunk a ship
                            playerTwoBoard.displayShipAsSunkOnShotsDisplay(shipWasSunk.second,
                                                                           playerOneBoard.getPopulatedPoints()); // update your shots map show that
                            playerOneBoard.displayShipAsSunkOnShipsDisplay(
                                    shipWasSunk.second); // make opponent update their ships map so they know it's sunk
                        } else { // ig the ship was not sunk
                            playerTwoBoard.recordOnShotsDisplay(position, 'X'); // update your shots map as a hit
                            playerOneBoard.recordOnShipsDisplay(position,
                                                                'X'); //make opponent update their ships map as a hit

                        }
                    } else {
                        playerTwoBoard.recordOnShotsDisplay(position, '*');
                        playerOneBoard.recordOnShipsDisplay(position, '*');
                    }
                }
            } else {
                playerTwoBoard.recordOnShotsDisplay(shotPoint, '*');
                playerOneBoard.recordOnShipsDisplay(shotPoint, '*');
            }
            playerOnesTurn = true;
        }
        cout << "Game will either end on next loop or next player will play" << endl;
    }
}

list<pair<string, int>> Game::generateMineLocations(const list<Point> &populatedPoints) {
    list<pair<string, int>> minesToReturn;

    for (int i = 0; i < 5; ++i) {
        while (true) {
            int x = (rand() % playerOneBoard.getLength()) + 1;
            int y = (rand() % playerOneBoard.getHeight()) + 1;
            bool positionTakenByShip = false;
            bool positionTakenByAnotherMine = false;

            for (Point point : populatedPoints) {
                if (point.getCoordinates().first == x && point.getCoordinates().second == y) {
                    positionTakenByShip = true;
                }
            }

            for (pair<string, int> minePosition: minesToReturn) {
                if (minePosition.first == intToLetterss(x) && minePosition.second == y) {
                    positionTakenByAnotherMine = true;
                }
            }

            if (!positionTakenByShip && !positionTakenByAnotherMine) {
                cout << intToLetterss(x) << ", " << y << endl;
                minesToReturn.push_back(pair(pair(intToLetterss(x), y)));
                break;
            }
        }
    }
    cout << endl;
    return minesToReturn;
}

list<pair<string, int>> Game::positionsHitByExplosion(pair<string, int> mineLocation) {
    int length = numberFromExcelColumnn(mineLocation.first);
    int height = mineLocation.second;
    list<pair<string, int>> positionsToReturn;
    if (height > 1) {
        positionsToReturn.push_back(pair(mineLocation.first, height - 1));
        if (length > 1) {
            positionsToReturn.push_back(pair(intToLetterss(length - 1), height - 1));
        }
        if (length < playerOneBoard.getLength()) {
            positionsToReturn.push_back(pair(intToLetterss(length + 1), height - 1));
            positionsToReturn.push_back(pair(intToLetterss(length + 1), height));
        }
    }
    if (height < playerOneBoard.getHeight()) {
        positionsToReturn.push_back(pair(mineLocation.first, height + 1));
        if (length > 1) {
            positionsToReturn.push_back(pair(intToLetterss(length - 1), height + 1));
        }
        if (length < playerOneBoard.getLength()) {
            positionsToReturn.push_back(pair(intToLetterss(length + 1), height + 1));
            positionsToReturn.push_back(pair(intToLetterss(length + 1), height));
        }
    }

    if (length > 1) {
        positionsToReturn.push_back(pair(intToLetterss(length - 1), height));
    }

    if (length < playerOneBoard.getLength()) {
        positionsToReturn.push_back(pair(intToLetterss(length + 1), height));
    }
    return positionsToReturn;
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