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
	
	cout << "przekierowanie: stdin -> program0 -> program1 -> ... -> program4 -> stdout" << endl; 
		
	run_in_pipeline(p, 5, false); 

	cout << endl << "a teraz z przekierowaniem deskryptorów typu >, <" << endl; 
	cout << "testutils/test.in -> program0 -> ... -> program4 -> testutils/test.out"  << endl; 
	
	FILE *in, *out; 
	in = fopen("testutils/test.in", "r"); 
	out = fopen("testutils/test.out", "w+"); 
	
	run_with_in_out_redirect(fileno(in), fileno(out), p, 5, false); 
	

	return 0; 
}
