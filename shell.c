#include "shell.h"

extern char **environ; 

int SUBSHELL_ID; 

int run(); 

int main(int argc, char* argv[]) {
/*	if (argc > 1) 
		SUBSHELL_ID = atoi(argv[1]); 
	else 
		SUBSHELL_ID = 1; 
		
	while (1) {
		// wczytaj linię
		// parsuj
		// przeglądaj odpowiednio otrzymaną strukturę i wywołuj funkcje api
	}
*/ 

	read_from_file("test2/eloelo"); 
	
	return 0; 
}

