
parsing:
	gcc -std=c99 -Wall -Werror -g -c src/parsing.c -o bin/parsing.o

document:
	gcc -std=c99 -Wall -Werror -g -c src/document.c -o bin/document.o

main: document parsing
	gcc -std=c99 -Wall -Werror -g src/main.c bin/parsing.o bin/document.o -o bin/main

test_doc: document
	gcc -std=c99 -Wall -Werror -g src/main.c bin/document.o -o bin/test_doc

all: main

test: document parsing
	gcc -std=c99 -Wall -Werror -g src/test.c bin/parsing.o bin/document.o -o bin/test

run: all
	chmod +x bin/main
	./bin/main
