#include <algorithm>          /* For std::max */
#include "minimax.h"

inline const signed char get_max(const signed char a, const signed char b)
{
		return std::max(a, b);
}

inline const signed char get_min(const signed char a, const signed char b)
{
		return std::min(a, b);
}


/* Minimax function. */
const signed char minimax(const minimaxNode* node, const char depth, signed char alpha, signed char beta, bool max)
{
    /* Base Case, leaf node. */
    if (!node->children or !depth)
    {
        return heur(node);
    }

	signed char ret, other;
	const signed char (*min_or_max) (const signed char, const signed char);
	if (max)
	{
		ret = alpha;
		other = beta;
		min_or_max = &get_max;
	}
	else
	{
		ret = beta;
		other = alpha;
		min_or_max = &get_min;
	}

    /* Recursive Step, using max everytime, but doing *-1 at each step. */
    for (minimaxNode *child = node->children; child != NULL; child = child->next)
    {
		if (max)
            ret = min_or_max(ret, (signed char)(minimax(child, depth-1, ret, other, !max)));
		else
            ret = min_or_max(ret, (signed char)(minimax(child, depth-1, other, ret, !max)));
        if (ret >= other)
           break;
    }
	return ret;
}

/* Heuristic function */
inline const signed char heur(const minimaxNode* n)
{
     /* At this point just retrieve value, optionally sleep. */
     return (signed char) n->value;
}
