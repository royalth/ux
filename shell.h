#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

int do_cd(char*);
int do_pwd();
int do_ls();
int do_ls_path(char*);
int do_touch(char*); 

int read_from_file(char*); 
int write_to_file(char*, char*); 

int run_in_pipeline(char***, int, bool); 
int run_with_in_out_redirect(int, int, char***, int, bool);
