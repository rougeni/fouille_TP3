
parsing:
	gcc -O3 -std=gnu99 -Wall -Werror -g -c src/parsing.c -o bin/parsing.o

rand:
	gcc -O3 -Wall -Werror -g -c src/rand.c -o bin/rand.o

document:
	gcc -O3 -std=gnu99 -Wall -Werror -g -c src/document.c -o bin/document.o
	
bernoulli: document
	gcc -O3 -std=gnu99 -Wall -Werror -g -c src/bernoulli.c bin/document.o -o bin/bernoulli.o

multinomial: document
	gcc -O3 -std=gnu99 -Wall -Werror -g -c src/multinomial.c bin/document.o -o bin/multinomial.o

main: document parsing rand bernoulli multinomial
	gcc -O3 -std=gnu99 -Wall -Werror -g src/main.c bin/parsing.o bin/document.o bin/rand.o bin/multinomial.o bin/bernoulli.o -o bin/main

test_doc: document
	gcc -O3 -std=gnu99 -Wall -Werror -g src/test_doc.c bin/document.o -o bin/test_doc

all: main

test: document parsing
	gcc -O3 -std=gnu99 -Wall -Werror -g src/test.c bin/parsing.o bin/document.o -o bin/test

run: all
	chmod +x bin/main
	./bin/main
