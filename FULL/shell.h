#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <stdlib.h>
#include "parser.h"
#pragma once

int do_cd(char*);
int do_pwd();
int do_ls();
int do_ls_path(char*);
int do_touch(char*); 

int read_from_file(char*); 
int write_to_file(char*, char*); 

int run_in_pipeline(char***, int, bool); 							// proga arg1 | prog2 arg1 arg2 | prog3 | prog4
int run_with_in_out_redirect(int, int, char***, int, bool);	// proga < in.in > out.out
char* run_and_get_output(char***, int);							// proga `progb` - ta funkcja uzyskuje to co podstawiamy zamiast progb
int run_child_shell(char*, bool, int);								// wywołanie danej linii w podshellu: ( linia )

char*** prepare_command_line(command_line*, int*); 
char** prepare_command_segment(command_segment*); 
char* prepare_command_invocation_part(command_invocation_part*); 

void print_command_line(command_line* line);
void print_command_invocation_part(command_invocation_part*); 
void print_command_invocation(command_invocation_part*);
void print_subshell(subshell*);
void print_command_segment(command_segment*); 
