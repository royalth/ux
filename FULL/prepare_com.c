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

char** prepare_command_segment(command_segment *segment) { // TODO SUBSZEL
	command_invocation_part *part = segment->data.command; 
	int num = 0; 
	while (part != NULL) {
		num++; 
		part = part->next; 
	}
	if (num == NULL) return NULL; 

	char** res = malloc(sizeof(char*) * (1+num) ); // jeden więcej, bo jeszcze null na końcu

	part = segment->data.command; 
	int i = 0; 
	while (part != NULL) {
		res[i++] = prepare_command_invocation_part(part); 
		part = part->next; 
	}
	res[num] = NULL; 

	return res; 
}

char* prepare_command_invocation_part(command_invocation_part *part) { // TODO inne typy, gł redirect tylko jeśli to jest pierwszy/ostatni element
	return part->data.string; 

	// jeśli ARGUMENT_COMMAND_SUBSTITUTION to wywołać tutaj run_and_get_output i podstawić pod return wynik
}









