#include "shell.h"
#include <iostream>
using namespace std; 

int run_in_pipeline(char** programs[], int program_num, bool background) {
	if (program_num == 0) {
		return 1; 
	}
	
	int i, j; 
	int fd[program_num-1][2]; 
	for (i = 0; i < program_num-1; ++i) {
		pipe(fd[i]); 
	}
	
	pid_t pids[program_num]; 
	for (i = 0; i < program_num; ++i) {
		if ( (pids[i] = fork()) == 0) {
	
			if (i != 0) {					// tylko w pierwszym nie przekierowujemy in
				dup2(fd[i-1][0], 0); 
			}
			
			if (i != program_num-1) {	// tylko w ostatnim nie przekierowujemy out
				dup2(fd[i][1], 1); 
			}
		
			for (j = 0; j < program_num-1; ++j) {
				close(fd[j][0]); 
				close(fd[j][1]); 
			}
			
			execv(programs[i][0], programs[i]); 
			
			fprintf( stderr, "Error executing program: %s\n", strerror(errno));
			
			exit(1); 
		}
	}
	
	for (j = 0; j < program_num-1; ++j) {
		close(fd[j][0]); 
		close(fd[j][1]); 
	}
	
	if (background == false) {
		// nie są uruchamiane w tle, więc czekamy na zakończenie ich działania
		int status;
		for (i = 0; i < program_num; ++i) {
			waitpid(pids[i], &status, 0); 
		}
	}
	
	return 0; 		
}


