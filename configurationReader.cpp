#include <iostream>
#include <map>
#include <fstream>
#include <vector>

#include "configurationReader.h"

using namespace std;

pair<string, vector<string>> keyValueParser(string line) {
bool parsingKey = true;
bool firstValueParsed = false;

string key = "";
vector<string> values = {"", ""};
for (string::size_type i = 0; i < line.size(); i++) {

  if (line[i] == ':') { // finished reading the key
    parsingKey = false;
    i++; // skips empty space
    continue;
  }

  if (parsingKey) {
    key += line[i]; // adds char to key 
  } else {
    // different value delimiters are used depedning on key
    
    if (key.compare("Board") == 0) { 
      if (line[i] == 'x') {
        firstValueParsed = true;
        continue;
      }

      if (!firstValueParsed) {
        values[0] += line[i];
      } else {
        values[1] += line[i];
      }

    } else {

      if (line[i] == ',') {

        firstValueParsed = true;
        i++; // skipping empty space after ,
        continue;
      }

      if (!firstValueParsed) {
        values[0] += line[i];
      } else {
        values[1] += line[i];
      }
    }
  }
}
return make_pair(key, values);
}

map<string, vector<string>> getConfiguration (){
map<string, vector<string>> mapToReturn;
string line;
ifstream fileobject;

fileobject.open("adaship_config.ini");

while(!fileobject.eof()){
  getline(fileobject, line); //reads line from file
  pair<string, vector<string>> keyValue = keyValueParser(line); // pairs key and value
  mapToReturn.insert({keyValue.first, keyValue.second}); // creates entry in map
}
fileobject.close(); //closing ini file
return mapToReturn;
}

