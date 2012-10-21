#ifndef READXML_H
#define READXML_H

#include <libxml/parser.h>
#include "minimax.h"

const char * const xmlfilename = "tree.xml";
const minimaxNode* readxmltree(const char* const filename);
const minimaxNode* readxmlnode(const xmlNode* const root,
	                      const minimaxNode* const parent);
#endif
