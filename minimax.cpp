#include <algorithm>          /* For std::max */
#include <pthread.h>
#include <assert.h>
#include <vector>
#include <string.h>
#include "minimax.h"
#include "gameinfo.h"

MinimaxNode::MinimaxNode(const unsigned char * const board, const signed char position, const unsigned char player_no)
   : children(NULL)
   , next(NULL)
   , last_pos(position)
{
	if(board)
		memcpy(this->board, board, 64);
	this->board[position] = player_no;
}

MinimaxNode::~MinimaxNode()
{
	if(next)
		delete next;
	next = NULL;
	if(children)
		delete children;
	children = NULL;
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

	if (check_win(last_pos, board, left_turn? 1 : 2))
		return -50;

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
