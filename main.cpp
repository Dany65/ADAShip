#include <iostream>
#include <map>
#include <vector>

#include "gameController.h"
#include "configurationReader.h"


using namespace std;

int main() {
  gameController *controller = gameController::getInstance(getConfiguration());
}