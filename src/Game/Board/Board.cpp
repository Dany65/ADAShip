//
// Created by boris on 3/4/21.
//

#include <regex>
#include "Board.h"

void display(vector<vector<char>> toDisplay) {
    for(int i = 0; i < toDisplay.size(); i++)
    {
        for(int j = 0; j < toDisplay[0].size(); j++)
        {
            cout << toDisplay[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<char>> createShotsDisplay(int length, int height) {  //TODO: finish Coordinates part
    vector<vector<char>> vec( height , vector<char> (length));

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < length; j++)
        {
            vec[i][j] = '0';
        }
    }

    cout << "Shots Display:" << endl;
    display(vec);
    return vec;
}

vector<vector<char>> createShipsDisplay(int length, int height) {
    vector<vector<char>> vec( height , vector<char> (length));

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < length; j++)
        {
            vec[i][j] = '0';
        }
    }

    cout << "Ships Display:" << endl;
    display(vec);
    return vec;
}

Board::Board(int length, int height, map<string, Ship> ships):
length_(length),
height_(height),
ships_(ships),
shipsDisplay(createShipsDisplay(length, height)),
shotsDisplay(createShotsDisplay(length, height))
//populatedPoints(populatePoints(length, height, ships)){
{}


//vector<Point> Board::populatePoints(int length, int height, map<string, Ship> ships) {
//    cout << "Time to place your ships.";
//    display(shipsDisplay);
//
//    vector<Point> pointsToReturn;
//    bool shipsPlaced = false;
//
//    do {
//        display(shipsDisplay);
//        cout << "Which ship would you like to place: " << endl;
//        // TODO: Print out ships list
//        string shipName;
//        getline(cin, shipName);
//        bool shipExists = (ships.count(shipName) == 1);
//        //check if ship has been placed already and if so, pick up
//        if (shipExists) {
//            Ship ship = ships.find(shipName)->second;
//
//            pair<pair<string, int>, char> placementInstructions = getPlacementInstructions();
////            bool isAllowed = shipCanBePlaced(placementInstructions, ship.getLength(), pointsToReturn);
////TODO:: implement shipCanBePLaced
//
////            if (isAllowed){
////
////            }
//            //            bool isAllowed = canBePlaced(placementInstructions, ships.find(shipName)->second.getLength());
//        } else {
//            cout << "Ship is not on the list, try again." << endl;
//        }
//    } while (shipsPlaced); //TODO: make !
//
//    return vector<Point>();
//}

pair<pair<string, int>, char> Board::getPlacementInstructions() {
    string placementInstructions; // A1, H
    do {
        cout << "Placement instructions should be in the format of A2, H";
        getline(cin, placementInstructions);
    } while (!isCorrectlyFormatted(placementInstructions));

    pair<pair<string, int>, char> formattedInstructions = splitInstructions(placementInstructions);
}


bool Board::isCorrectlyFormatted(string instructions) {
    // format AB, 25

    if (instructions.find(", ") != std::string::npos) {
        string coordinates = instructions.substr(0, instructions.find(','));
        bool coordinatesMatch = std::regex_match(coordinates, std::regex("^[A-Za-z]{1,}[1-9]{1,}$")); // true

        string secondHalf = instructions.substr(instructions.find(' ')+1);
        bool orientationMatches = std::regex_match(secondHalf, std::regex("^[hHvV]{1}$"));

        return (coordinatesMatch && orientationMatches);
    }
    return false;
}


pair<pair<string, int>, char> Board::splitInstructions(string instructions) { //TODO: FINISH THIS

    string coordinates = instructions.substr(0, instructions.find(','));
    string letterCoordinates = returnMatch(coordinates, "^[A-Za-z]{1,}");
    std::transform(letterCoordinates.begin(), letterCoordinates.end(), letterCoordinates.begin(), ::toupper);
    string numberCoordinate = coordinates.substr(letterCoordinates.length());

    string orientation = instructions.substr(instructions.find(' ')+1);

    return pair(pair(letterCoordinates, stoi(numberCoordinate)), toupper(orientation[0]));
}

string Board::returnMatch(string stringToUse, string regexToFind) const {
    smatch match;
    regex_search(stringToUse, match, std::regex(regexToFind));
    return match.str();
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
