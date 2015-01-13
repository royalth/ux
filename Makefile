shell: shell.c shell.h built_in_operations.c file_operations.c run.c 
	gcc shell.c built_in_operations.c file_operations.c run.c -o shell 

test_pipeline: run.c shell.h testprog test_pipeline.cpp
	g++ test_pipeline.cpp run.c -o test_pipeline -std=c++11
