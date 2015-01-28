#include "shell.h"

void print_command_invocation_part(command_invocation_part* part) {
	switch(part->type) {
		case ARGUMENT_STRING:
			printf("STRING(%s) ", part->data.string);
			break;
		case ARGUMENT_REDIRECT:
			printf("REDIRECT(%d, %c, %s) ", part->data.redirect->redirected_fd, (part->data.redirect->direction == REDIRECT_DIRECTION_OUT ? '>' : '<'), part->data.redirect->destination_path);
			break;
		case ARGUMENT_COMMAND_SUBSTITUTION:
			printf("SUBSTITUTE_COMMAND_LINE (look for a \"begin command_line\")\n");
			print_command_line(part->data.substitute_command_line);
			break;
	}
}

void print_command_invocation(command_invocation_part* first_part) {
	command_invocation_part* current_part = first_part;
	while(current_part != NULL) {
		print_command_invocation_part(current_part);
		current_part = current_part->next;
	}
	printf("\n");
}

void print_subshell(subshell* subshell) {
	printf("begin subshell\n");
	print_command_line(subshell->child_command_line);
	print_command_invocation(subshell->first_redirect);
	printf("end subshell\n");
}

void print_command_segment(command_segment* segment) {
	printf("begin command_segment\n");
	switch(segment->type) {
		case COMMAND_SEGMENT_COMMAND:
			printf("this is a command invocation segment:\n");
			print_command_invocation(segment->data.command);
			break;
		case COMMAND_SEGMENT_SUBSHELL:
			printf("this is a subshell segment:\n");
			print_subshell(segment->data.subshell);
			break;
	}
	printf("end command_segment\n");
}

void print_command_line(command_line* line) {
	printf("begin command_line [%s]\n", line->run_in_background ? "&" : " ");
	command_segment* current_segment = line->first_command_segment;
	while(current_segment != NULL) {
		print_command_segment(current_segment);
		current_segment = current_segment->next;
	}
	printf("end command_line\n");
}
