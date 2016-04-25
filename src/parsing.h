#ifndef DEF_PARSING
#define DEF_PARSING
#include "document.h"

struct document* parseBase(char filename[]);

struct document* parseLine(char line[]);

struct mot* parseMot(char word[]);

#endif
