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
	MinimaxNode(const unsigned char * const, const signed char, const unsigned char);	
	~MinimaxNode();
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

class GainParams
{
public:
   	const unsigned char * const board; 
	const unsigned char index:6;
	const unsigned char mul:2;
	const unsigned char player:2;
	const signed char sign:2;
	GainParams(const unsigned char *, const unsigned char, const unsigned char, 
			   const unsigned char, const signed char);
};

void * count_gain(void *);

#endif
