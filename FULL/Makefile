all: bison flex compile testprogs

bison:
	bison -d command_line.y

flex:
	flex command_line.l

compile:
	gcc -std=c99 -o shell shell.c parser.c command_line.tab.c lex.yy.c print_com.c run.c prepare_com.c built_in_operations.c -lfl -w

testprogs:
	g++ testprog.c -o testprog
	g++ testprog_long.c -o testprog_long
