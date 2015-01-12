#include "shell.h"

const int MAX_PATH_LENGTH = 32000; 

int do_pwd() {
	char buffer[MAX_PATH_LENGTH]; 
	if ( getcwd(buffer, MAX_PATH_LENGTH) == NULL) 
		return 1;
		
	printf(" %s\n", buffer); 
	
	return 0; 
}

int do_ls() {
	char buffer[PATH_MAX]; 
	if ( getcwd(buffer, MAX_PATH_LENGTH) == NULL) 
		return 1;
	DIR *d = opendir(buffer); 
	if ( d == NULL )
		return 2; 
	
	struct dirent *dir;
	int num, name_l; 
	char buff[256]; 
	while ( (dir = readdir(d)) != NULL) {
		printf("  %s\n", dir->d_name); 
	}
	
	closedir(d);
	return 0; 
}

int do_cd(char* path) {
	if ( chdir(path) != 0 ) 
		return 1; 
		
	return 0; 
}

int do_touch(char* pathname) {
	if ( access(pathname, F_OK) != -1 ) // plik istnieje
		return 1; 
	
	FILE *f = fopen(pathname, "ab+"); 
	if (f == NULL) 
		return 1; 
	
	fclose(f); 
	return 0; 
}


