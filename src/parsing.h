#ifndef DEF_PARSING
#define DEF_PARSING
#include "document.h"

struct document* parseBase(char filename[]);

void parseLine(struct document* ens_doc, char line[]);

void parseMot(struct document* doc, const char word[]);

#endif
