#include "modele.h"
#include <stdio.h>
#include <stdlib.h>


void supprimerModele(struct modele* M){
    free(M->Pi);
    for(int i = 0; i < 29; i++){
        struct probaOccurrence* probaCour = M->PC[i];
        while(M->PC[i] != NULL){
            M->PC[i] = M->PC[i]->suivante;
            free(probaCour);
            probaCour = M->PC[i];
        }
    }
    free(M->PC);
    free(M);
}
