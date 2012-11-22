#include <algorithm>          /* For std::max */
#include "minimax.h"

/* Minimax function. */
const signed char minimax(const minimaxNode* node, const char depth, signed char alpha, signed char beta, bool max)
{
    /* Base Case, leaf node. */
    if (!node->children or !depth)
    {
        return heur(node);
    }

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

    /* Recursive Step, using max everytime, but doing *-1 at each step. */
    for (minimaxNode *child = node->children; child != NULL; child = child->next)
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
inline const signed char heur(const minimaxNode* n)
{
     /* At this point just retrieve value, optionally sleep. */
     return (signed char) n->value;
}
