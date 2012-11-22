#include <algorithm>          /* For std::max */
#include <pthread.h>
#include <assert.h>
#include <vector>
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

	signed char ret, other;
	if (max)
	{
		ret = alpha;
		other = beta;
	}
	else
	{
		ret = beta;
		other = alpha;
	}

    for (MinimaxNode *child = node->children; child != NULL; child = child->next)
    {
		if (max)
            ret = std::max(ret, (signed char)(minimax(child, depth-1, ret, other, !max)));
		else
            ret = std::min(ret, (signed char)(minimax(child, depth-1, other, ret, !max)));
        if (ret >= other)
           break;
    }
	return ret;
}

/* Heuristic function */
inline const signed char MinimaxNode::heur(bool left_turn) const
{
	std::vector<pthread_t> threads;
	signed char ret = 0;

	for (unsigned char i = 0; i < 64; ++i)
	{
		if (!board[i])
		{
			continue;
		}
		for (unsigned char j = 0; j < 4; ++j)
		{
			pthread_t t;
			assert(0 == pthread_create(&t, NULL, count_gain, (void *) new GainParams(board, i, j, board[i], (left_turn ^ (board[i] == 2) ? 1 : -1))));
			threads.push_back(t);
		}
	}

	while (!threads.empty())
	{
		signed char * pgain;
	    assert(0 == pthread_join(threads.back(), (void **) &pgain));
		ret += *pgain;
		delete(pgain); pgain = NULL;
		threads.pop_back();
	}
	
    /* At this point just retrieve value, optionally sleep. */
    return ret;
}

GainParams::GainParams(const unsigned char * board, const unsigned char index, 
		               const unsigned char mul, const unsigned char player, const signed char sign)
	: board(board)
	, index(index)
	, mul(mul)
	, player(player) 
	, sign(sign)
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
	void * ret = (void *) new signed char(params->sign * ((gain < 3)? 0: gain - 3));
	delete(params);
	return ret;
}
