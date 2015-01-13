#include "shell.h"

const int MAX_LINE_LENGTH = 10000; 

extern char **environ;
int SUBSHELL_ID; 

int handle_line(char*); 
run_child_shell(char*, bool); 

int main(int argc, char* argv[]) {
	if (argc > 2) {
		// wywołanie podshella; argv[1] to id, argv[2] to polecenia wywołane w podshellu
	
		SUBSHELL_ID = atoi(argv[1]); 
		printf("podshell\n"); 
		return handle_line(argv[2]); 
	}
	
	SUBSHELL_ID = 1; 
	
	printf("glowny shell\n"); 
	run_child_shell("polecenie do wykonania w podszelu", false); 
	
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

int run_child_shell(char* line, bool background) {
	int fd[2];
	if (pipe(fd) != 0) {
		perror("pipe"); 
	}
	//fcntl(fd[0], F_SETFL, O_NONBLOCK); 	// parent będzie pisał do tego pipe'a zanim będzie on miał jakiegokolwiek czytelnik

	printf("mam pajpa, zara bede pisau\n"); 

	if ( write(fd[1], line, strlen(line)) < 1 )  {
		printf("o kutfa buont: %s\n", strerror(errno)); 
		return 1; 
	}
	
	printf("jednak siem nie zablokowauem\n"); 
	
	
	pid_t child; 
	if ( (child = fork()) == 0 ) {
		dup2(fd[0], 0); 
		close(fd[0]); 
		close(fd[1]); 
		
		char** p[1];
		p[0] = (char**) malloc(sizeof(char*) * 4); 
		p[0][0] = (char*) malloc(sizeof(char) * 10); 
		strcpy( p[0][0], "shell" ); 
		p[0][1] = (char*) malloc(sizeof(char) * 10);
		sprintf(p[0][1], "%d", SUBSHELL_ID + 1);
		p[0][2] = (char*) malloc(sizeof(char) * strlen(line)); 
		strcpy(p[0][2], line); 
		p[0][3] = NULL; 
		
		run_in_pipeline(p, 1, background); 
		
		exit(1);
	}
	
	int status = 0; 
	if (!background) 
		waitpid(child, &status, 0); 
	
	close(fd[0]); 
	close(fd[1]);  
		
	return status; 
}







