
parsing:
	gcc -Wall -Werror -g -c src/parsing.c -o bin/parsing.o

main: 
	gcc -Wall -Werror -g -c src/main.c -o bin/main

all: main

run:
	chmod +x bin/main
	./bin/main
	