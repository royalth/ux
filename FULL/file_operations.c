#include "shell.h"

int read_from_file(char* filename) {
	FILE *f = fopen(filename, "r"); 
	if ( f == NULL ) {
		fprintf( stderr, "Error opening file: %s\n", strerror(errno));
		return 1; 
	}
	char buffer[1024];
	int num; 
	while ( fscanf(f, "%s", buffer) > 0 ) {
		printf("%s", buffer); 
	}
	
	fclose(f); 
	return 0;
}

int write_to_file(char* filename, char* text) {
	FILE *f = fopen(filename, "w+"); 
	if ( f == NULL ) {
		fprintf( stderr, "Error opening file: %s\n", strerror(errno));
		return 1; 
	}
	
	if ( fprintf(f, "%s", text) < 0 ) {
		fclose(f);
		fprintf( stderr, "Error writing to file\n");
		return 1; 
	}
	
	fclose(f); 
	return 0;	
}


