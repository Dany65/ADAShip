//
// Created by boris on 3/4/21.
//

#include <regex>
#include<cmath>
#include <algorithm>
#include "Board.h"

int numberFromExcelColumn(string column) {
    int retVal = 0;
    for (int iChar = column.length() - 1; iChar >= 0; iChar--) {
        char colPiece = column[iChar];
        int colNum = colPiece - 64;
        retVal = retVal + colNum * (int) pow(26, column.length() - (iChar + 1));
    }
    return retVal;
}

void display(vector<vector<char>> toDisplay) {
    for (int i = 0; i < toDisplay.size(); i++) {
        for (int j = 0; j < toDisplay[0].size(); j++) {
            cout << toDisplay[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<char>> createShotsDisplay(int length, int height) {  //TODO: finish Coordinates part
    vector<vector<char>> vec(height, vector<char>(length));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < length; j++) {
            vec[i][j] = '0';
        }
    }

//    cout << "Shots Display:" << endl;
//    display(vec);
    return vec;
}


bool isCorrectlyFormatted(string instructions) {
    // format AB, 25

    if (instructions.find(", ") != std::string::npos) {
        string coordinates = instructions.substr(0, instructions.find(','));
        bool coordinatesMatch = std::regex_match(coordinates, std::regex("^[A-Za-z]{1,}[1-9]{1,}$")); // true

        string secondHalf = instructions.substr(instructions.find(' ') + 1);
        bool orientationMatches = std::regex_match(secondHalf, std::regex("^[hHvV]{1}$"));

        return (coordinatesMatch && orientationMatches);
    }
    return false;
}

vector<vector<char>> createShipsDisplay(int length, int height) {
    vector<vector<char>> vec(height, vector<char>(length));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < length; j++) {
            vec[i][j] = '0';
        }
    }

//    cout << "Ships Display:" << endl;
//    display(vec);
    return vec;
}

Board::Board(int length, int height, map<string, Ship> ships) :
        length_(length),
        height_(height),
        ships_(ships),
        shipsDisplay(createShipsDisplay(length, height)),
        shotsDisplay(createShotsDisplay(length, height)) {
}


list<Point> Board::returnPointsToPopulate() {
    list<string> shipsToPlace;
    for (const auto& pair : ships_) {
        shipsToPlace.push_back(pair.first);
    }
    list<string> placedShips;

    cout << "Time to place your ships." << endl;

    list<Point> pointsToReturn = {};
    bool allShipsPlaced = false;

    string shipName;
    do {
        display(shipsDisplay);
        cout << "Which ship would you like to place: " << endl;
        cout << "Ships you can relocate: ";
        for (string shipsToPlace : placedShips) {
            cout << shipsToPlace << ", ";
        }
        cout << endl;
        cout << "You have to place: ";
        for (string placableShipName : shipsToPlace) {
            cout << placableShipName << ", ";
        }
        cout << endl;


        getline(cin >> ws, shipName);
        bool shipExist = (ships_.count(shipName) == 1);
        bool shipPlaced = (any_of(placedShips.begin(), placedShips.end(), [&](const string& elem) { return elem == shipName; }));
        // Next use new variable shipsToPlace  to check if it has been placed

        if (shipExist && !shipPlaced) {
            shared_ptr<Ship> ship_ptr = make_shared<Ship>(ships_.find(shipName)->second);

            pair<pair<string, int>, char> placementInstructions = getPlacementInstructions();
            bool isAllowed = shipCanBePlaced(length_, height_, placementInstructions, ship_ptr->getLength(), pointsToReturn);

            if (isAllowed) {
                placeShip(placementInstructions, ship_ptr, &pointsToReturn);

                for (Point point : pointsToReturn) {
                    cout << point.getShip()->getName() << endl;
                    cout << point.getCoordinates().first << ", " << point.getCoordinates().second << endl;
                }

                updateShipsDisplay(pointsToReturn);
                placedShips.push_back(shipName);
                shipsToPlace.remove(shipName);
                cout << "Ship Placed" << endl << endl;
            }
        } else if (shipPlaced){ //TODO: implement placement
            cout << "This ship has already been placed" << endl;
        }
        else {
            cout << "Ship is not on the list, try again." << endl;
        }
    } while (!shipsToPlace.empty()); //TODO: make !

    return pointsToReturn;
}

pair<pair<string, int>, char> Board::getPlacementInstructions() {
    string placementInstructions; // A1, H
    bool isInputValid;
    do {
        cout << "Placement instructions should be in the format of A2, H:" << endl;
        getline(cin >> ws, placementInstructions);
    } while (!isCorrectlyFormatted(placementInstructions));

    return splitInstructions(placementInstructions);
}


pair<pair<string, int>, char> Board::splitInstructions(string instructions) { //TODO: FINISH THIS

    string coordinates = instructions.substr(0, instructions.find(','));
    string letterCoordinates = returnMatch(coordinates, "^[A-Za-z]{1,}");
    std::transform(letterCoordinates.begin(), letterCoordinates.end(), letterCoordinates.begin(), ::toupper);
    string numberCoordinate = coordinates.substr(letterCoordinates.length());

    string orientation = instructions.substr(instructions.find(' ') + 1);

    return pair(pair(letterCoordinates, stoi(numberCoordinate)), toupper(orientation[0]));
}

string Board::returnMatch(string stringToUse, string regexToFind) {
    smatch match;
    regex_search(stringToUse, match, std::regex(regexToFind));
    return match.str();
}

bool Board::shipCanBePlaced(int length, int height, pair<pair<string, int>, char> placementInstructions, int shipLength,
                            list<Point> takenUpPositions) {

    if (placementInstructions.second == 'H') { // if horizontal placement
        cout << placementInstructions.first.first << "   " << length << endl;
        cout << placementInstructions.first.second << "   " << height << endl;
        if ((numberFromExcelColumn(placementInstructions.first.first) + shipLength - 1 <= length) &&
            placementInstructions.first.second <= height) { // ship fits on map putting ship right
            if (!willOverlapAnotherShip(placementInstructions, shipLength,
                                        takenUpPositions)) { // ship will not overlap another
                return true;
            }
            cout << "Invalid choice, another ship is in teh way" << endl;
            return false;
        }
        cout << "Invalid choice, ship will be outside of the map" << endl;
        return false;
    } else { // if vertical placement
        if (numberFromExcelColumn(placementInstructions.first.first) <= length &&
            placementInstructions.first.second + shipLength - 1 <= height) { // ship fits on map putting ship up
            if (!willOverlapAnotherShip(placementInstructions, shipLength,
                                        takenUpPositions)) { // ship will not overlap another
                return true;
            }
            cout << "Invalid choice, another ship is in the way" << endl;
            return false;
        }
        cout << "Invalid choice, ship will be outside of the map" << endl;
        return false;
    }
}

bool Board::willOverlapAnotherShip(pair<pair<string, int>, char> placementInstructions, int shipLength,
                                   list<Point> takenUpPoints) {
    if (placementInstructions.second == 'H') {
        int startingPosition = numberFromExcelColumn(placementInstructions.first.first);
        for (int i = 0; i < shipLength; ++i) { // tests each position
            for (Point point : takenUpPoints) {
                if (point.getCoordinates().second == placementInstructions.first.second &&
                    point.getCoordinates().first == startingPosition + i) {
                    return true;
                }
            }
        }
    } else {
        int const xCoordinate = numberFromExcelColumn(placementInstructions.first.first);
        int startingPosition = placementInstructions.first.second;
        for (int i = 0; i < shipLength; ++i) { // tests each position
            for (Point point : takenUpPoints) {
                if (point.getCoordinates().first == xCoordinate &&
                    point.getCoordinates().second == startingPosition + i) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Board::setShotsDisplay(const vector<vector<char>> &shotsDisplay) {
    Board::shotsDisplay = shotsDisplay;
}

void Board::setShipsDisplay(const vector<vector<char>> &shipsDisplay) {
    Board::shipsDisplay = shipsDisplay;
}

void Board::setPopulatedPoints(const list<Point> &populatedPoints) {
    Board::populatedPoints = populatedPoints;
}

void Board::placeShip(pair<pair<string, int>, char> placementInstruction, shared_ptr<Ship> ship, list<Point> *populatedPoints) {
    int xCoordinate = numberFromExcelColumn(placementInstruction.first.first);

    for (int i = 0; i < ship->getLength(); ++i) {
        if (placementInstruction.second == 'H') {
            populatedPoints->push_back(Point(pair{xCoordinate+i, placementInstruction.first.second}, ship));
        } else {
            populatedPoints->push_back(Point(pair{xCoordinate, placementInstruction.first.second+i}, ship));
        }
    }
}

void Board::updateShipsDisplay(list<Point> populatedPoints) {
    for (Point point : populatedPoints) {
        shipsDisplay[point.getCoordinates().second-1][point.getCoordinates().first-1] = point.getShip()->getName()[0];
    }
}

//pair<string, string> Board::splitInstructions(string) {
//
//    return pair<string, string>();
//}

//cout << "Place your ships:";
////    vector<vector<char>> shipsDisplay;
//vector<vector<char>> shipsDisplay( length , vector<char> (height, 0));
//
//for(int i = 0; i < length; i++)
//{
//for(int j = 0; j < height; j++)
//{
//cout << shipsDisplay[i][j] << " ";
//}
//cout<< endl;
//}
//
//
//vector<Point> populatedPoints;
//
//vector<vector<char>> shotsDisplay;

//Board::Board(int length, int height, vector<Ship> ships):
//length_(length), height_(height), ships_(ships)
//{
//cout << "HI"
//}
