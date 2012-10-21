#ifndef MINIMAX_H
#define MINIMAX_H

#include <climits>            /* For SCHAR_MIN */

/* Struct of tree of minimax search */
struct minimaxNode 
{
    const signed char value;                  /* Heuristic value or value for heuristic */
    struct minimaxNode* children;             /* Link to the first child */
    const struct minimaxNode* const parent;   /* Link to the parent */
    struct minimaxNode* next;                 /* Link to next sibling */
};

const signed char heur(const minimaxNode* n);
/* Set alpha to -infinity and beta to +infinity, in this case, 
 * minimum and maximum CHAR values */
const signed char minimax(const minimaxNode* n, const char depth, 
                          signed char alpha=SCHAR_MIN, 
                          signed char beta=SCHAR_MAX, 
                          bool max=true);
#endif
