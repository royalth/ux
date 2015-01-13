#include "shell.h"

const int MAX_LINE_LENGTH = 10000; 

int SUBSHELL_ID; 

int handle_line(char*); 

int main(int argc, char* argv[]) {
	if (argc > 2) {
		// wywołanie podshella; argv[1] to id, argv[2] to polecenia wywołane w podshellu
	
		SUBSHELL_ID = atoi(argv[1]); 
		printf("podshell\n"); 
		return handle_line(argv[2]); 
	}
	
	SUBSHELL_ID = 1; 
	
	printf("glowny shell\n"); 
	run_child_shell("polecenie do wykonania w podszelu", false, SUBSHELL_ID); 
	
	/* prawdziwe działanie shella
	char buffer[MAX_LINE_LENGTH]
	while (1) {
		getline
		handle_line
	}
	*/ 
	
	return 0; 
}

int handle_line(char* line) {
	// parsuj
	// przeglądaj otrzymaną strukturę
	// wywołuj funkcje api
	
	printf("handle line: %s\n", line); 
	return 0;
}








