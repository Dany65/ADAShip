#include <iostream>
#include <map>
#include <vector>
#include "Game/Ship/Ship.h"
#include "Game/Point/Point.h"
#include "Game/Board/Board.h"

#include "configurationReader/ConfigurationReader.h"
#include "Menu.h"


using namespace std;

int main() {
//    vector<int> userConfiguration =  Menu::gameSetUpSequence();
//    map<string, vector<string>> fileConfiguration = ConfigurationReader::getConfiguration();

//    pair<string, int> coordinates = {"A", 2};

    Ship ship("Titanik", 2);
    Point point({"A", 2},&ship);
    map<string, Ship> ships;
    ships.insert({ship.getName(), ship});
    Board board(4, 2, ships);

    cout << endl <<board.splitInstructions("ABB012323, H").second << endl;

//    if(board.isCorrectlyFormatted("A2, sh")){
//        cout << "YIPI";
//    } else {
//        cout << "NOPE";
//    }
//    pair<string, int> yey = board.splitInstructions("B, 0");
//    cout << yey.first << "  " << yey.second;

//    GameController gameConroller(Game::Game() game,userConfiguration,fileConfiguration);
//
//    Game game = Game(userConfiguration, fileConfiguration);
//
//   GC *controller = GC::getInstance(userConfiguration, fileConfiguration);

//   gameCotroller.startgame()
//  Ship* myShip = new Ship("dot", 1);

}