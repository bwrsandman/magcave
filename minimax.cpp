#include <algorithm>          /* For std::max */
#include "minimax.h"

void * get_max(void * p)
{
	return new (signed char)(std::max(((const signed char*)p)[0], ((const signed char*)p)[1]));
}

void * get_min(void * p)
{
	return new (signed char)(std::min(((const signed char*)p)[0], ((const signed char*)p)[1]));
}


/* Minimax function. */
const signed char minimax(const minimaxNode* node, const unsigned char depth, signed char ret, signed char other, bool max)
{
    /* Base Case, leaf node. */
    if (!node->children or !depth)
        return heur(node);


	void * (*min_or_max) (void *) = 
		(max)? &get_max : &get_min;
    for (minimaxNode *child = node->children; child != NULL; child = child->next)
    {
		const signed char p[2] = {ret, (signed char)(minimax(child, depth-1, other, ret, !max))};
        const signed char *pret = (const signed char *)min_or_max((void *)p);
		ret = *pret;
		delete(pret);
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
