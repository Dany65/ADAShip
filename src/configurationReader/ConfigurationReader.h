#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
using namespace std;
class ConfigurationReader{
public:
    static map<string, vector<string>> getConfiguration();
};
#endif