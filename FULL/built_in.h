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

int do_cd(char*);
int do_pwd();
int do_ls();
int do_ls_path(char*);
int do_touch(char*); 
