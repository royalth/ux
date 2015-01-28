#include "built_in.h"

int main(int argc, char* argv[]) {
	if (argc < 2)
		do_ls(); 
	else
		do_ls_path(argv[1]); 

	return 0; 
}
