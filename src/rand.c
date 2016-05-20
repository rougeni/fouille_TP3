#include "rand.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* fonction utilisateur de comparaison fournie a qsort() */
static int compare (void const *a, void const *b)
{
   /* definir des pointeurs type's et initialise's
      avec les parametres */
   int const *pa = a;
   int const *pb = b;

   /* evaluer et retourner l'etat de l'evaluation (tri croissant) */
   return *pa - *pb;
}

int* tabRand(int taille, int tailleEntrainement){

    int* resultat=malloc((taille)*sizeof (int));
    int i=0;

    // On remplit le tableau de manière à ce qu'il soit trié

    for(i = 0; i< taille; i++){
        resultat[i]=i;
    }

    int nombre_tire=0;
    int temp=0;
    srand(time(NULL));
    
    for(i = 0; i< taille;i++){
        nombre_tire = rand()%taille;

        // On échange les contenus des cases i et nombre_tire
        temp = resultat[i];
        resultat[i] = resultat[nombre_tire];
        resultat[nombre_tire]=temp;
    }

    qsort(resultat, tailleEntrainement, sizeof *resultat, compare); 

    return resultat;

}




