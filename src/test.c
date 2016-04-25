#include "parsing.h"
#include "document.h"
#include <stdio.h>


int main (int argc, char **argv){
	struct document test;
	parseMot(&test,"0:0");
	printf("Test 0:0 => %i:%i\n",test.vecteur[0].indice, test.vecteur[0].nombre_occurence);

	struct document *ensemble_doc = NULL;
	parseLine(ensemble_doc,"1 1:1 2:2 3:3");
	return 0;
}
