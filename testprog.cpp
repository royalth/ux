#include <iostream>
using namespace std; 

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "niepoprawna liczba argumentów!" << endl; 
		return 1; 
	}
	
	string s;
	cin >> s; 
	cout << s << "_" << argv[1]; 
	
	return 0; 
}
