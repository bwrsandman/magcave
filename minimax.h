#ifndef MINIMAX_H
#define MINIMAX_H

#include <climits>            /* For SCHAR_MIN */

/* Struct of tree of minimax search */
class MinimaxNode
{
    unsigned char board[64];
	public:
    const unsigned char * const get_board(){return board;}
    MinimaxNode* children;             /* Link to the first child */
    MinimaxNode* next;                 /* Link to next sibling */
	const unsigned char last_pos:6;
	MinimaxNode(const unsigned char * const, const signed char, const unsigned char);
	~MinimaxNode();
	const signed char heur(bool left_turn = true) const;
};

const unsigned char DEPTH_DEFAULT = 2;

/* Set alpha to -infinity and beta to +infinity, in this case,
 * minimum and maximum CHAR values */
const signed char _minimax(const MinimaxNode*,
						  const unsigned char,
						  bool,
                          signed char,
                          signed char);

const signed char minimax(const MinimaxNode* a,
						  const unsigned char b,
						  bool c);

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
