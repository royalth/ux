#include "shell.h"

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

int run_with_in_out_redirect(int in_fd, int out_fd, char** programs[], int program_num, bool background) {
	pid_t child; 
	if ( (child = fork()) == 0) {
		if (in_fd != 0) {
			dup2(in_fd, 0); 
			close(in_fd); 
		}
		
		if (out_fd != 1) {
			dup2(out_fd, 1); 
			close(out_fd); 
		}
		
		int res = run_in_pipeline(programs, program_num, background); 
		exit(res); 
	}
	
	int status; 
	waitpid(child, &status, 0); 
	
	return status; 
}


char* run_and_get_output(char** programs[], int program_num) {
	int fd[2]; 
	pipe(fd); 

	pid_t child; 
	if ( (child = fork()) == 0) {
		int res = run_with_in_out_redirect(0, fd[1], programs, program_num, false);
		exit(res); 
	}
	
	int status; 
	waitpid(child, &status, 0); 

	int buff_size = 10000; 	
	char* buffer = (char*)malloc(buff_size*sizeof(char)); 
	int num; 
	if ( (num = read(fd[0], buffer, buff_size-1)) < 0 ) {
		perror("buffer read"); 
	}
	
	return buffer; 
}



