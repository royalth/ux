#include "shell.h"

char*** prepare_command_line(command_line *line, int *size) {
	command_segment *segment = line->first_command_segment; 
	int num = 0; 
	while (segment != NULL) {
		num++; 
		segment = segment->next; 
	}
	if (num == 0) return NULL; 

	char*** res = malloc(sizeof(char**) * num); 

	segment = line->first_command_segment; 
	int i = 0; 
	while (segment != NULL) {
		res[i++] = prepare_command_segment(segment); 
		segment = segment->next; 
	}
	*size = num; 
	return res; 
}

char** prepare_command_segment(command_segment *segment) { 
	switch(segment->type) {
		case COMMAND_SEGMENT_COMMAND:
			return prepare_command_segment_invocation(segment->data.command); 
			
		case COMMAND_SEGMENT_SUBSHELL: // TODO SUBSZEL
			return NULL; 
	}
}
	
char** prepare_command_segment_invocation(command_invocation_part *first) {
	command_invocation_part *part = first; 
	int num = 0; 
	while (part != NULL) {
		num++; 
		part = part->next; 
	}
	if (num == NULL) return NULL; 

	char** res = malloc(sizeof(char*) * (1+num) ); // jeden więcej, bo jeszcze null na końcu

	part = first; 
	int i = 0; 
	while (part != NULL) {
		res[i++] = prepare_command_invocation_part(part); 
		part = part->next; 
	}
	res[num] = NULL; 

	return res; 
}

char* prepare_command_invocation_part(command_invocation_part *part) { // TODO co jeśli nule w środku?
	int size; 
	char*** programs;
	switch(part->type) {
		case ARGUMENT_STRING:
			return part->data.string; 

		case ARGUMENT_REDIRECT: // TODO ???
			return NULL; 

		case ARGUMENT_COMMAND_SUBSTITUTION:
			programs = prepare_command_line(part->data.substitute_command_line, &size); 
			return run_and_get_output(programs, size); 
	}
}









