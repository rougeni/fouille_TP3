#ifndef DEF_PARSING
#define DEF_PARSING
#include "document.h"

struct document* parseBase(char filename[]);

struct document* parseLine(struct document* ens_doc, const char * line);

void parseMot(struct document* doc, const char * word);

#endif
