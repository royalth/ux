shell: shell.c shell.h built_in_operations.c file_operations.c run_pipeline.c 
	gcc shell.c built_in_operations.c file_operations.c run_pipeline.c -o shell 

test_pipeline: run_pipeline.c shell.h testprog test_pipeline.cpp
	g++ test_pipeline.cpp run_pipeline.c -o test_pipeline -std=c++11
