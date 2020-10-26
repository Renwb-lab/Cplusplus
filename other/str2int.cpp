#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int str2int(string s) {
     stringstream ss(s);
     int result = 0;
     ss >> result;
     return result;        
}

int main(int argc, char* argv[]) {
	cout << str2int(string("123")) << endl;
}
