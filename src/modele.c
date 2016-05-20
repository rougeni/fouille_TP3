#include "modele.h"
#include <stdio.h>
#include <stdlib.h>


void supprimerModele(struct modele* M){
    free(M->Pi);
    for(int k = 0; k < 29; k++) free(M->PC[k]);
    free(M->PC);
    free(M);
}
