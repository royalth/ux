all: bison flex compile

bison:
	bison -d command_line.y

flex:
	flex command_line.l

compile:
	gcc -std=c99 -o main main.c parser.c command_line.tab.c lex.yy.c -lfl
