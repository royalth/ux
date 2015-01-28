#include <stdbool.h>
#pragma once

enum argument_type { ARGUMENT_STRING, ARGUMENT_COMMAND_SUBSTITUTION, ARGUMENT_REDIRECT };
enum command_segment_type { COMMAND_SEGMENT_COMMAND, COMMAND_SEGMENT_SUBSHELL };
enum redirect_direction { REDIRECT_DIRECTION_IN, REDIRECT_DIRECTION_OUT };

// Forward declarations:
typedef struct redirect redirect;
typedef struct subshell subshell;
typedef struct command_line command_line;

typedef struct command_invocation_part {
	enum argument_type type;
	struct command_invocation_part* next;
	union {
		// In case of a simple string argument, it is stored here:
		char* string;
		// For command substitutions, we point at the command line to execute in order to get the computed value:
		command_line* substitute_command_line;
		// For redirects, we need to store both the descriptor number and the destination file path:
		redirect* redirect;
	} data;
} command_invocation_part;

struct redirect {
	enum redirect_direction direction;
	int redirected_fd;
	char* destination_path;
};

typedef struct command_segment {
	enum command_segment_type type;
	struct command_segment* next;
	union {
		// If the command segment type is a normal command, point to its initial command invocation part:
		command_invocation_part* command;
		// Otherwise, if the segment is a sub-shell, point at the command line.
		subshell* subshell;
	} data;
} command_segment;



/*
 * A Sub-shell holds the information about the complete command-line to call in a forked copy of ourselves, as well as redirections from/to the child shell process. 
 */
struct subshell {
	command_line* child_command_line;
	// If any redirections have been requested for the child process, the redirect list (as represented by command invocation parts) will be non-empty. Otherwise, NULL.
	// Note that we assume every command invocation part must be of type ARGUMENT_REDIRECTION in this list.
	command_invocation_part* first_redirect;
};

/*
 * A command substitution (such as `this`) is much like a sub-shell, but it does not allow external specification of redirects.
 * This means that, when calling "echo `date` >date.txt a b c", the redirect belongs to the top-level command_segment and is not associated with the substitution.
 */
// typedef struct command_substitution {
// 	
// };

/*
 * A Command Line represents a sequence of piped command invocations or subshells. Each element of the linked list shall be piped from left to right.
 */
struct command_line {
	bool run_in_background;
	command_segment* first_command_segment;
};
