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
	
	char buffer[MAX_LINE_LENGTH]; 
	int len; 
	while (1) {
		printf("\n> "); 
		if ( fgets(buffer, MAX_LINE_LENGTH, stdin) == NULL ) { 
			perror("fgets"); 
			continue; 
		}

		handle_line(buffer); 
	}
	
	return 0; 
}

int handle_line(char* line) {
	command_line* parsed = parse_command_line(line);
	if (parsed == NULL) {
		return 1; 
	}	

//	print_command_line(parsed);

	int size; 
	char*** programs = prepare_command_line(parsed, &size); 

	run_in_pipeline(programs, size, parsed->run_in_background); 

	for (int i = 0; i < size; ++i) {
		for (int j = 0; programs[i][j] != NULL; ++j) {
			free(programs[i][j]); 
		}
		free(programs[i]); 
	}

	return 0;
}








