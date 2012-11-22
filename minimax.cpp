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
		{
			signed char * pgain = (signed char *) count_gain((void *) new GainParams(board, i, j, board[i]));
			points[board[i]-1] += *pgain;
			delete(pgain); pgain = NULL;
		}
	}
	
    /* At this point just retrieve value, optionally sleep. */
    return (signed char) (points[0]-points[1]) * (left_turn ? 1 : -1);
}

GainParams::GainParams(const unsigned char * board, const unsigned char index, 
		               const unsigned char mul, const unsigned char player)
	: board(board)
	, index(index)
	, mul(mul)
	, player(player) 
{
}

void * count_gain(void * vparams)
{
	GainParams * params = (GainParams *)vparams;
	unsigned char gain = 0;
	const unsigned char mults[4] = {1, 8, 7, 9};
	unsigned char opponent = params->player ^ 0x3;
	signed char position = params->index;
	
	// Backwards
	for(unsigned char i = 1; i < 5; ++i)
	{
		position = params->index - mults[params->mul] * i;
		if( (params->mul == 0 && position % 8 == 7) || (params->mul == 1 && position > params->index) ||
			(params->mul == 2 && position % 8 == 0) || (params->mul == 3 && position % 8 == 7) )
			break;
		else if(position < 0 || params->board[position] == opponent)
			break;
		else
			++gain;
	}
	// Forwards
	for(unsigned char i = 1; i < 5; ++i)
	{
		position = params->index + mults[params->mul] * i;
		if( (params->mul == 0 && position % 8 == 0) || (params->mul == 1 && position < params->index) ||
            (params->mul == 2 && position % 8 == 7) || (params->mul == 3 && position % 8 == 0) )
			break;
		else if(position > 63 || params->board[position] == opponent)
			break;
		else
			++gain;
	}
	delete(params);
	return (void *) new signed char((gain < 3)? 0: gain - 3);
}
