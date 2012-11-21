#ifndef MINIMAX_H
#define MINIMAX_H

#include <climits>            /* For SCHAR_MIN */

/* Struct of tree of minimax search */
class MinimaxNode 
{
	public:
    MinimaxNode* children;             /* Link to the first child */
    MinimaxNode* next;                 /* Link to next sibling */
	unsigned char *board;
	MinimaxNode(unsigned char * const);
	const signed char heur(bool left_turn = true) const;
};

const unsigned char DEPTH_DEFAULT = 5;

/* Set alpha to -infinity and beta to +infinity, in this case, 
 * minimum and maximum CHAR values */
const signed char minimax(const MinimaxNode* n,
						  const unsigned char depth,
                          signed char alpha=SCHAR_MIN, 
                          signed char beta=SCHAR_MAX, 
                          bool max=true);
inline signed char count_gain(const unsigned char, const unsigned char * const, const unsigned char, const unsigned char);
#endif
