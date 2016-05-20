#ifndef DEF_MODELE
#define DEF_MODELE

struct probaOccurrence;
struct probaOccurrence{
	int indice;
	double proba;
	struct probaOccurrence* suivante;
        struct probaOccurrence* precedente;
};

struct modele;
struct modele{
  //tableau de la distribution des classes
  double* Pi;
  //tableau des probabilites d'occurence des termes pour chaque classe
  struct probaOccurrence** PC;
};


struct modeleMultinomial;
struct modeleMultinomial{
    struct modele modeleM;
    int* denomPC;
};

#endif
