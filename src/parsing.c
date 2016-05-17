#include "parsing.h"
#include <stdlib.h>
#include <string.h>


//TO BE REMOVED
#include <stdio.h>

void parseMot(struct document* doc,const char * word) {
  if (word ==  NULL) {
    return;
  }

  if (*word ==  '\0' || *word == ' ')
    return;

  if (strlen(word) <= 1)
    return;

  char * wrd = strdup(word);
  int i = 0;
  int indice;
  int nbr_occur;
  while (wrd[i] != ':') {
    i++;
  }
  wrd[i] = '\0';
  indice = atoi(wrd);
  nbr_occur = atoi(wrd+i+1);
  free(wrd);
  ajouter_mot(doc,indice,nbr_occur);
}

struct document* parseLine(struct document* ens_doc, const char * line) {
  char *buf = NULL;
  char **bp = NULL;
  char *tok = NULL;
  int cat;
  struct document* ens_docu;
	
  buf = strdup(line);
  bp = &buf;

  tok = strsep(bp, " ");
  cat = atoi(tok);

  ens_docu = creer_document(ens_doc,cat);
	
  while((tok = strsep(bp, " ")) != NULL){
    parseMot(ens_docu,tok);
  }
	
  free(buf);
  return ens_docu;
}


struct document* parseBase(const char *filename) {
  struct document* ens_doc = NULL;

  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error : can't open file!\n");
    exit(EXIT_FAILURE);
  }

  int i = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    ens_doc = parseLine(ens_doc,line);
    i++;
  }

  fclose(fp);

  free(line);
  return ens_doc;

}
