#include <algorithm>          /* For std::max */
#include "minimax.h"

MinimaxParams::MinimaxParams(const minimaxNode* node, const unsigned char depth, signed char ret, signed char other, bool max)
	: node(node)
	, depth(depth)
	, max(max)
	, ret(ret)
	, other(other)
{
}

inline const signed char get_max(const signed char a, const signed char b)
{
		return std::max(a, b);
}

inline const signed char get_min(const signed char a, const signed char b)
{
		return std::min(a, b);
}


/* Minimax function. */
signed char * minimax(MinimaxParams *vparams)
{
	MinimaxParams params = *vparams;
	delete(vparams); vparams = NULL;
	signed char ret = params.ret;
    /* Base Case, leaf node. */
    if (!params.node->children or !params.depth)
        return new (signed char)(heur(params.node));

	const signed char (*min_or_max) (const signed char, const signed char) = 
		(params.max)? &get_max : & get_min;

    for (minimaxNode *child = params.node->children; child != NULL; child = child->next)
    {
		signed char * p;
        ret = min_or_max(params.ret, (signed char)(*(p=minimax(
							new MinimaxParams(child, params.depth-1, 
								params.other, ret, !params.max)))));
		delete p;
        if (ret >= params.other)
           break;
    }
	return new (signed char)(ret);
}

/* Heuristic function */
inline const signed char heur(const minimaxNode* n)
{
     /* At this point just retrieve value, optionally sleep. */
     return (signed char) n->value;
}
