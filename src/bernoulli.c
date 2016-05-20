#include "bernoulli.h"
#include <stdlib.h>
#include <math.h>



void modifTabPCkBernoulli(double* PCk, struct mot* doc){

    struct mot* courMot = doc;
    
    while( courMot != NULL ){
        PCk[courMot->indice - 1]++;
        courMot = courMot->suivant;    
    }
  
}



void determinerParametresBernoulli(double* tabPi,double** tabPC, struct document* ensemble_documents, int nbDocuments, int V){

    struct document* docCour = ensemble_documents;
    
    while ( docCour != NULL ){
        
        tabPi[docCour->categorie - 1]++;
        modifTabPCkBernoulli(tabPC[docCour->categorie-1], docCour->vecteur);
        
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
  double* tabPi = malloc( nbClasses*sizeof(double) );
  //tableau des probabilites d'occurence des termes pour chaque classe
  double** tabPC = malloc(nbClasses*sizeof(double*));
  
  for(int k = 0; k < nbClasses; k++){
      tabPi[k] = 0;
      tabPC[k] = calloc(sizeof(double), V);
  }

  determinerParametresBernoulli(tabPi, tabPC, ensemble_documents, nbDocuments, V);

  struct modele* modele = malloc( sizeof(struct modele) );
  modele->Pi = tabPi;
  modele->PC = tabPC;
  
  

  return modele;

}


int testBernoulli(struct document* doc, int V, int nbClasses, struct modele* modeleApprentissage){
    
    double PiF;
    double PiFMax;
    int kMax = 1;
    
    for(int k = 0; k < nbClasses; k++){
        int i = V;
        PiF = log((modeleApprentissage->Pi)[k]);
        struct mot* d = doc->vecteur;
        while (i > 0){
            if(d != NULL){
                if (d->indice == i){
                    PiF += log(modeleApprentissage->PC[k][i]);
                    d = d->suivant;
                }
            }
            else PiF += log(1 - modeleApprentissage->PC[k][i]);
            
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







