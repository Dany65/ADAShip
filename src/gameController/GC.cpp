//#include <iostream>
//#include <map>
//#include <vector>
//using namespace std;
//
//class GC {
//private:
//  GC(const vector<int> userConfiguration, const map<string, vector<string>> fileConfigurationData):
//  userConfiguration_(userConfiguration),
//  fileConfigurationData_(fileConfigurationData)
//  {
//      cout << "\ngameController created";
//  };
//
//  static GC* inst_;
//  map<string, vector<string>> fileConfigurationData_;
//  vector<int> userConfiguration_;
//
//public: //essentially, public means everyone is allowed to access
//		GC(GC &other) = delete; //execute a delete - singletons should not be cloneable.
//    void operator=(const GC &) = delete; //execute a delete - singletons should not be assignable.
//   	~GC() {} //destructor
//
//		//define the static method to control access to the singleton instance
//		//initially, it will create a new singleton object and places it into the static field.
//		//on later calls, it simply returns the original object instance stored in the static field.
//		static GC *getInstance(const vector<int> userConfiguration, const map<string, vector<string>> fileConfigurationData);
//
//		std::string businessLogic(std::string data) {
//			//...
//			return "doing something really useful: " + data;
//		}
//
//    // std::string reference() const {
//    //     return reference_;
//    // }
//
//		// int value() const {
//		// 	return value_;
//		// }
//
//};
//
//GC* GC::inst_= nullptr;
//
//GC *GC::getInstance(const vector<int> userConfiguration, const map<string, vector<string>> fileConfigurationData) {
//
//	if(inst_== nullptr){ // only triggarable if a singleton has not been created yet
//		inst_ = new GC(userConfiguration, fileConfigurationData);
//	}
//	return inst_; // returning the singleton
//}