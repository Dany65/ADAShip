#include <map>
#include <vector>
#include "Game/Game.h"
#include "configurationReader/ConfigurationReader.h"
#include "Menu.h"


using namespace std;


int main() {
    vector<int> userConfiguration = Menu::gameSetUpSequence();
    map<string, vector<string>> fileConfiguration = ConfigurationReader::getConfiguration();

    Game game(fileConfiguration);
    game.startGame(userConfiguration);
}