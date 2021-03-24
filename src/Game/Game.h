//
// Created by boris on 3/4/21.
//

#ifndef ADASHIP_GAME_H
#define ADASHIP_GAME_H

#include <iostream>
#include <vector>
#include <map>
#include <Game/Board/Board.h>


using namespace std;

class Game {

public:
    Game(map<string, vector<string>> fileConfiguration);

    void startGame(vector<int> userConfiguration);
private:
    Board playerOneBoard;
    Board playerTwoBoard;

    void initialiseShips(int gameType); // TODO move out of class
    void beginShootingSequence(vector<int> userConfiguration);

    void normalShooterGame(vector<int> userConfiguration);

    void salvoShooterGame(vector<int> userConfiguration);

    void minesGame(vector<int> vector);

    list<pair<string, int>> generateMineLocations(const list<Point> &populatedPoints);

    list<pair<string, int>> positionsHitByExplosion(pair<string, int> mineLocation);
};


#endif //ADASHIP_GAME_H
