
parsing:
	gcc -Wall -Werror -g -c src/parsing.c -o bin/parsing.o

document:
	gcc -Wall -Werror -g -c src/document.c -o bin/document.o

main: document parsing
	gcc -Wall -Werror -g src/main.c bin/parsing.o bin/document.o -o bin/main


all: main

test: document parsing
	gcc -Wall -Werror -g src/test.c bin/parsing.o bin/document.o -o bin/test

run: all
	chmod +x bin/main
	./bin/main
