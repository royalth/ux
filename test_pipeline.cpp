#include "shell.h"
#include <iostream>
#include <typeinfo>
using namespace std; 

int main() {
	char** p[6]; 
	
	for (char c = 0; c < 5; ++c) {
		p[c] = new char* [3]; 
		
		p[c][0] = new char [100]; 
		strcpy(p[c][0], "testprog"); 
		
		p[c][1] = new char[1]; 
		p[c][1][0] = c+48; 
		
		p[c][2] = NULL;
	}
		
	run_in_pipeline(p, 5, false); 

	return 0; 
}
