#include <algorithm>          /* For std::max */
#include "minimax.h"

MinimaxNode::MinimaxNode(unsigned char * const board)
   : board(board)
{
}

/* Minimax function. */
const signed char minimax(const MinimaxNode* node, const unsigned char depth, signed char alpha, signed char beta, bool max)
{
    /* Base Case, leaf node. */
    if (!node->children or !depth)
        return node->heur();

    /* Recursive Step, using max everytime, but doing *-1 at each step. */
    if (max)
    {
        for (MinimaxNode *child = node->children; child != NULL && beta > alpha; child = child->next)
            alpha = std::max(alpha, (signed char)(minimax(child, depth-1, alpha, beta, !max)));
        return alpha;
    }
    else
    {
        for (MinimaxNode *child = node->children; child != NULL && alpha > beta; child = child->next)
            beta = std::min(beta, (signed char)(minimax(child, depth-1, alpha, beta, !max)));
        return beta;
    }
}

/* Heuristic function */
inline const signed char MinimaxNode::heur(bool left_turn) const
{
	int points[2] = {0, 0};

	for (unsigned char i = 0; i < 64; ++i)
	{
		if (!board[i])
		{
			continue;
		}
		for (unsigned char j = 0; j < 4; ++j)
			points[board[i]-1] += count_gain(board[i], board, i, j);
		
	}
	
    /* At this point just retrieve value, optionally sleep. */
    return (signed char) (points[0]-points[1]) * (left_turn ? 1 : -1);
}

inline signed char count_gain(const unsigned char player, const unsigned char * const board, 
		                      const unsigned char index, const unsigned char mul)
{
	unsigned char gain = 0;
	const unsigned char mults[4] = {1, 8, 7, 9};
	unsigned char opponent = player ^ 0x3;
	signed char position = index;
	
	// Backwards
	for(unsigned char i = 1; i < 5; ++i)
	{
		position = index - mults[mul] * i;
		if( (mul == 0 && position % 8 == 7) || (mul == 1 && position > index) ||
			(mul == 2 && position % 8 == 0) || (mul == 3 && position % 8 == 7) )
			break;
		else if(position < 0 || board[position] == opponent)
			break;
		else
			++gain;
	}
	// Forwards
	for(unsigned char i = 1; i < 5; ++i)
	{
		position = index + mults[mul] * i;
		if( (mul == 0 && position % 8 == 0) || (mul == 1 && position < index) ||
            (mul == 2 && position % 8 == 7) || (mul == 3 && position % 8 == 0) )
			break;
		else if(position > 63 || board[position] == opponent)
			break;
		else
			++gain;
	}
	return (gain < 3)? 0: gain - 3;
}
