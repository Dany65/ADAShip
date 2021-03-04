#include <iostream>
#include <map>
#include <fstream>
#include <vector>

#include "configurationReader.h"

using namespace std;

pair<string, vector<string>> parseBoat(string basicString);

pair<string, vector<string>> parseBoard(string line);


pair<string, vector<string>> keyValueParser(string line) {

//checking what we are defining
    bool isBoatDefinition;
    if (line[3] == 'r') {
        isBoatDefinition = false;
    } else { isBoatDefinition = true; }

//setting starting point for key value parsing
    if (isBoatDefinition) {
        return parseBoat(line);
    } else {
        return parseBoard(line);
    }
}


pair<string, vector<string>> parseBoard(string line) {
    pair<string, vector<string>> pairToReturn;

    string key = "Board";
    vector<string> dimensions = {"", ""};



    bool firstValueParsed = false;
    for (string::size_type i = 7; i < line.size(); i++) {
        if (line[i] == 'x') {
            firstValueParsed = true;
            continue;
        }

        if (firstValueParsed) {
            dimensions[1] += line[i];
        } else {
            dimensions[0] += line[i];
        }
    }

    pairToReturn.first = key;
    pairToReturn.second = dimensions;

    return pairToReturn;
}

pair<string, vector<string>> parseBoat(string line) {
    pair<string, vector<string>> pairToReturn;
    string key = "";
    vector<string> length = {""};

    bool keyParsed = false;
    for (string::size_type i = 6; i < line.size(); i++) {
        if (line[i] == ',') {
            keyParsed = true;
            i++; // skipping empty space after ,
            continue;
        }

        if (keyParsed) {
            length[0] += line[i];
        } else {
            key += line[i];
        }
    }

    pairToReturn.first = key;
    pairToReturn.second = length;

    return pairToReturn;
}

map<string, vector<string>> getConfiguration (){
map<string, vector<string>> mapToReturn;
string line;
ifstream fileobject;

fileobject.open("adaship_config.ini");

while(!fileobject.eof()){
  getline(fileobject, line); //reads line from file
  pair<string, vector<string>> keyValue = keyValueParser(line); // pairs key and value
  if (mapToReturn.count(keyValue.first)==0){
      mapToReturn.insert({keyValue.first, keyValue.second}); // creates entry in map
  }

}
for (const std::pair<string, vector<string>>& pair : mapToReturn) {
    cout << pair.first << endl;
}
fileobject.close(); //closing ini file
return mapToReturn;
}

//TODO: Make it so the Same name can't be used twice