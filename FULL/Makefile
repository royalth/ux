all: bison flex compile testprogs built_in

bison:
	bison -d command_line.y

flex:
	flex command_line.l

compile:
	gcc -std=c99 -o shell shell.c parser.c command_line.tab.c lex.yy.c print_com.c run.c prepare_com.c -lfl -w

testprogs:
	g++ testprog.c -o testprog
	g++ testprog_long.c -o testprog_long

built_in:
	g++ do_ls.c built_in_operations.c -o ls
	g++ do_pwd.c built_in_operations.c -o pwd
	g++ do_cd.c built_in_operations.c -o cd
	g++ do_touch.c built_in_operations.c -o touch

