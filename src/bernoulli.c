#include "bernoulli.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>



void determinerParametresBernoulli(double* tabPi,double** tabPC, struct document* ensemble_documents, int nbDocuments, int V){

    struct document* docCour = ensemble_documents;
    
    while ( docCour != NULL ){
        
        tabPi[docCour->categorie - 1]++;
        
        struct mot* courMot = docCour->vecteur;
        
    
        while( courMot != NULL ){
            
           tabPC[docCour->categorie - 1][courMot->indice - 1]++;
           courMot = courMot->suivant; 

        }
        
        docCour = docCour->suivant;
        
    }
    
    for (int k = 0; k < 29 ; k++){
        
        int Nk = tabPi[k];
        for(int i = 0; i < V; i++){
            tabPC[k][i] = (tabPC[k][i] + 1)/(Nk + 2);
        }
        
        tabPi[k] /= nbDocuments;
          
    } 

}


struct modele* apprentissageBernoulli(int nbClasses, struct document* ensemble_documents, int nbDocuments, int V){

  //tableau de la distribution des classes
  double* tabPi = malloc(nbClasses*sizeof(double));
  //tableau des probabilites d'occurence des termes pour chaque classe
  double** tabPC = malloc(nbClasses*sizeof(double*));
  
  for(int k = 0; k < nbClasses; k++){
      tabPi[k] = 0;
      tabPC[k] = malloc(V*sizeof(double));
      for(int i = 0; i < V; i++) tabPC[k][i] = 0;
  }

  determinerParametresBernoulli(tabPi, tabPC, ensemble_documents, nbDocuments, V);

  struct modele* modele = malloc( sizeof(struct modele) );
  modele->Pi = tabPi;
  modele->PC = tabPC;
  
  

  return modele;

}


int testBernoulli(struct mot* doc, int V, int nbClasses, struct modele* modeleApprentissage){
    
    double PiF;
    double PiFMax = 0;
    int kMax = 1;
    
    for(int k = 0; k < nbClasses; k++){
        struct mot* d = doc;
        int i = V;
        PiF = log((modeleApprentissage->Pi)[k]);
        while (i > 0){
            if(d != NULL){
                if (d->indice == i){
                    PiF += log(modeleApprentissage->PC[k][i-1]);
                    d = d->suivant;
                }
                else PiF += log(1 - modeleApprentissage->PC[k][i-1]);
            }
            else PiF += log(1 - modeleApprentissage->PC[k][i-1]);
            
            i--;
        }
        
        if (k == 0){
            PiFMax = PiF;
        }
        else{
            if (PiFMax < PiF){
                PiFMax = PiF;
                kMax = k + 1;
            }
        }
        
        
    }
    
    return kMax;
    
}







