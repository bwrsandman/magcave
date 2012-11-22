#ifndef MINIMAX_H
#define MINIMAX_H

#include <climits>            /* For SCHAR_MIN */

/* Struct of tree of minimax search */
struct minimaxNode 
{
    const signed char value;                  /* Heuristic value or value for heuristic */
    struct minimaxNode* children;             /* Link to the first child */
    struct minimaxNode* next;                 /* Link to next sibling */
};

const char DEPTH_DEFAULT = 5;

class MinimaxParams
{
public:
	const minimaxNode * node;
	const unsigned char depth:7;
	bool max:1;
	const signed char ret;
	const signed char other;
	MinimaxParams(const minimaxNode*, const unsigned char, signed char=SCHAR_MIN, signed char=SCHAR_MAX, bool=true);
};

inline const signed char heur(const minimaxNode* n);
/* Set alpha to -infinity and beta to +infinity, in this case, 
 * minimum and maximum CHAR values */
signed char * minimax(MinimaxParams *);
#endif
