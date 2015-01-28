#include "built_in.h"

int main(int argc, char* argv[]) {
	if (argc > 1)
		do_cd(argv[1]); 

	return 0; 
}
