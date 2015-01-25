%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "parser.h"

command_invocation_part* create_invocation_part();
void append_command_invocation_part(command_invocation_part* destination, command_invocation_part* element);

%}

%code requires {
 
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif
 
}

%lex-param { yyscan_t scanner }
%parse-param { command_line** command_line_output }
%parse-param { yyscan_t scanner }

// Storage for the tokens read from the input:
%union {
	struct command_line* command_line;
	struct command_segment* command_segment;
	struct command_invocation_part* command_invocation;
	struct subshell* subshell;
	struct redirect* redirect;
	char* text;
	long number;
}

// Terminal symbol definitions:
%token WORD
%token PIPE
%token LPAREN
%token RPAREN
%token REDIRECT_IN
%token REDIRECT_OUT
%token AMPERSAND
%token NUMBER
%token SINGLE_QUOTE
%token ANYTHING_BUT_SINGLE_QUOTE
%token BACKTICK
%token SUBSTITUTION_START
%token UNKNOWN

// Debugging options:
%error-verbose

// Type definitions:
%type<text> WORD ANYTHING_BUT_SINGLE_QUOTE single_quoted_string file_path
%type<number> NUMBER
%type<command_line> command_line command_line_output
%type<redirect> redirect redirect_out redirect_in
%type<command_segment> piped_command_segments command_segment
%type<subshell> subshell subshell_bare
%type<command_invocation> command command_argument
%type<command_invocation> subshell_redirects
%type<command_invocation> command_substitution

%%

command_line_output:
	command_line { *command_line_output = $1; }
	;

command_line:
	piped_command_segments { $$ = create_command_line(false, $1); }
	| piped_command_segments AMPERSAND { $$ = create_command_line(true, $1); }
	;

piped_command_segments:
	command_segment { $$ = $1; }
	| piped_command_segments PIPE command_segment { $$ = $1; append_command_segment($$, $3); }
	;

command_segment:
	command { $$ = create_command_segment(COMMAND_SEGMENT_COMMAND); $$->data.command = $1; }
	| subshell { $$ = create_command_segment(COMMAND_SEGMENT_SUBSHELL); $$->data.subshell = $1; }
	;

subshell:
	subshell_bare { $$ = $1; }
	| subshell_bare subshell_redirects { $$ = $1; $$->first_redirect = $2; }
	;

subshell_bare:
	LPAREN command_line RPAREN { $$ = create_subshell($2); }
	;

subshell_redirects:
	redirect { $$ = create_invocation_part(ARGUMENT_REDIRECT); $$->data.redirect = $1; }
	| subshell_redirects redirect { $$ = $1; command_invocation_part* redirect_node = create_invocation_part(ARGUMENT_REDIRECT); redirect_node->data.redirect = $2; append_command_invocation_part($$, redirect_node);  }
	;

redirect:
	redirect_in { $$ = $1; }
	| redirect_out { $$ = $1; }
	;

redirect_out:
	REDIRECT_OUT file_path { $$ = create_redirect(REDIRECT_DIRECTION_OUT, STDOUT_FILENO, $2); }
	| NUMBER REDIRECT_OUT file_path { $$ = create_redirect(REDIRECT_DIRECTION_OUT, $1, $3); }
	;

redirect_in:
	REDIRECT_IN file_path { $$ = create_redirect(REDIRECT_DIRECTION_IN, STDIN_FILENO, $2); }
	| NUMBER REDIRECT_IN file_path { $$ = create_redirect(REDIRECT_DIRECTION_IN, $1, $3); }
	;
	
file_path:
	WORD { $$ = $1; }
	| NUMBER { char number_buffer[128]; snprintf(number_buffer, 128, "%ld", $1); $$ = strdup(number_buffer); }
	| single_quoted_string  { $$ = $1; }
	;

command:
	command_argument { $$ = $1; }
	| command command_argument { $$ = $1; append_command_invocation_part($$, $2); }
	;

command_argument:
	WORD { $$ = create_invocation_part(ARGUMENT_STRING); $$->data.string = $1; }
	| NUMBER { $$ = create_invocation_part(ARGUMENT_STRING); char number_buffer[128]; snprintf(number_buffer, 128, "%ld", $1); $$->data.string = strdup(number_buffer); }
	| command_substitution { $$ = $1; }
	| single_quoted_string { $$ = create_invocation_part(ARGUMENT_STRING); $$->data.string = $1; }
	| redirect { $$ = create_invocation_part(ARGUMENT_REDIRECT); $$->data.redirect = $1; }
	;

command_substitution:
	SUBSTITUTION_START command_line RPAREN { $$ = create_invocation_part(ARGUMENT_COMMAND_SUBSTITUTION); $$->data.substitute_command_line = $2; }
	;

single_quoted_string:
	SINGLE_QUOTE ANYTHING_BUT_SINGLE_QUOTE SINGLE_QUOTE { $$ = $2; }
	;

%%

int yyparse(command_line** command_line_output, yyscan_t scanner);
typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(char* str, yyscan_t scanner);

command_line* parse_command_line(char* command_line_input) {
	yyscan_t scanner;
	YY_BUFFER_STATE state;
	command_line* line = NULL;
	
	if(yylex_init(&scanner)) {
		return NULL;
	}
	
	state = yy_scan_string(command_line_input, scanner);
	if(yyparse(&line, scanner)) {
		return NULL;
	}
	
	yy_delete_buffer(state, scanner);
	yylex_destroy(scanner);
	
	return line;
}

int yyerror(command_invocation_part** command_invocation, yyscan_t scanner, char* const error_message) {
	printf("Problem exists between keyboard and chair: %s\n", error_message);
	return -1;
}