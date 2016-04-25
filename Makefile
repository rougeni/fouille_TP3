
parsing:
	gcc -std=gnu99 -Wall -Werror -g -c src/parsing.c -o bin/parsing.o

rand:
	gcc -Wall -Werror -g -c src/rand.c -o bin/rand.o

document:
	gcc -std=gnu99 -Wall -Werror -g -c src/document.c -o bin/document.o

main: document parsing rand
	gcc -std=gnu99 -Wall -Werror -g src/main.c bin/parsing.o bin/document.o bin/rand.o -o bin/main

test_doc: document
	gcc -std=gnu99 -Wall -Werror -g src/test_doc.c bin/document.o -o bin/test_doc

all: main

test: document parsing
	gcc -std=gnu99 -Wall -Werror -g src/test.c bin/parsing.o bin/document.o -o bin/test

run: all
	chmod +x bin/main
	./bin/main
