#include <iostream>
#include <map>
#include <vector>
using namespace std;

class gameController {
  private:
  gameController(const map<string, vector<string>> configurationData): 
			//initialising configuration
      configurationData_(configurationData)
			
      {
				
				cout << "\nsingleton contructor code started";
			}

		static gameController* inst_;

	protected: //essentially, protected means that members of subclasses are also allowed
		map<string, vector<string>> configurationData_;

  public: //essentially, public means everyone is allowed to access
		gameController(gameController &other) = delete; //execute a delete - singletons should not be cloneable.
    void operator=(const gameController &) = delete; //execute a delete - singletons should not be assignable.
   	~gameController() {} //destructor

		//define the static method to control access to the singleton instance 
		//initially, it will create a new singleton object and places it into the static field. 
		//on later calls, it simply returns the original object instance stored in the static field.
		static gameController *getInstance(const map<string, vector<string>> configurationData);

		std::string businessLogic(std::string data) {
			//...
			return "doing something really useful: " + data;
		}

    // std::string reference() const {
    //     return reference_;
    // }

		// int value() const {
		// 	return value_;
		// }
};

gameController* gameController::inst_= nullptr;

gameController *gameController::getInstance(const map<string, vector<string>> configurationData) {

	if(inst_== nullptr){ // only triggarable if a singleton has not been created yet
		inst_ = new gameController(configurationData);
	}
	return inst_; // returning the singleton 
}