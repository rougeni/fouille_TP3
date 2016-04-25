
parsing:
	gcc -Wall -Werror -g -c src/parsing.c -o bin/parsing.o

main: parsing
	gcc -Wall -Werror -g src/main.c bin/parsing.o -o bin/main

all: main

run: all
	chmod +x bin/main
	./bin/main
