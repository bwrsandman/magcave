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
const signed char minimax(const minimaxNode* node, const char depth, signed char ret, signed char other, bool max)
{
    /* Base Case, leaf node. */
    if (!node->children or !depth)
        return heur(node);

	const signed char (*min_or_max) (const signed char, const signed char) = 
		(max)? &get_max : & get_min;

    for (minimaxNode *child = node->children; child != NULL; child = child->next)
    {
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
