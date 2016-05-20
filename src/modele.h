#ifndef DEF_MODELE
#define DEF_MODELE

struct modele;
struct modele{
  //tableau de la distribution des classes
  double* Pi;
  //tableau des probabilites d'occurence des termes pour chaque classe
  double** PC;
};

void supprimerModele(struct modele* M);


struct modeleMultinomial;
struct modeleMultinomial{
    struct modele modeleM;
    int* denomPC;
};

#endif
