#include <stdbool.h>
#include <stddef.h>
#include "parser.h"

command_invocation_part* create_invocation_part(enum argument_type type) {
	//printf("create_invocation_part\n");
	command_invocation_part* created_part = malloc(sizeof(command_invocation_part));
	created_part->next = NULL;
	created_part->type = type;
	return created_part;
}

redirect* create_redirect(enum redirect_direction direction, int redirected_fd, char* destination_path) {
	redirect* created_redirect = malloc(sizeof(redirect));
	created_redirect->direction = direction;
	created_redirect->redirected_fd = redirected_fd;
	created_redirect->destination_path = destination_path;
	return created_redirect;
}

subshell* create_subshell(command_line* child_command_line) {
	subshell* created_subshell = malloc(sizeof(subshell));
	created_subshell->child_command_line = child_command_line;
	created_subshell->first_redirect = NULL;
	return created_subshell;
}

command_segment* create_command_segment(enum command_segment_type type) {
	command_segment* created_segment = malloc(sizeof(command_segment));
	created_segment->type = type;
	created_segment->next = NULL;
	return created_segment;
}

command_line* create_command_line(bool run_in_background, command_segment* first_command_segment) {
	command_line* created_line = malloc(sizeof(command_line));
	created_line->run_in_background = run_in_background;
	created_line->first_command_segment = first_command_segment;
	return created_line;
}

void append_command_segment(command_segment* destination, command_segment* element) {
	while(destination->next != NULL) {
		destination = destination->next;
	}
	destination->next = element;
}

void append_command_invocation_part(command_invocation_part* destination, command_invocation_part* element) {
	// First, find the end of the list:
	while(destination->next != NULL) {
		destination = destination->next;
	}
	// Append the element as the last element - the final destination's "next".
	destination->next = element;
}
