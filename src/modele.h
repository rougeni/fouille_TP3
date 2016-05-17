#ifndef DEF_MODELE
#define DEF_MODELE

struct probaOccurence;
struct probaOccurence{
	int indice;
	double proba;
	struct probaOccurence* suivante;
};

struct modeleBernoulli;
struct modeleBernoulli{
  //tableau de la distribution des classes
  double* tabProbaClasse;
  //tableau des probabilites d'occurence des termes pour chaque classe
  struct probaOccurence** tabProbaOccurence;
};

struct modeleMultinomial;
struct modeleMultinomial{
  //tableau de la distribution des classes
  double* tabProbaClasse;
  double* D;
  //tableau des probabilites d'occurence des termes pour chaque classe
  struct probaOccurence** tabProbaOccurence;
};

#endif
