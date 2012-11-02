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
    /* Recursive Step, using max everytime, but doing *-1 at each step. */
    if (max)
    {
        for (minimaxNode *child = node->children; child != NULL; child = child->next)
        {
            alpha = std::max(alpha, (signed char)(minimax(child, depth-1, alpha, beta, !max)));
            if (beta <= alpha)
                break;
        }
        return alpha;
    }
    else
    {
        for (minimaxNode *child = node->children; child != NULL; child = child->next)
        {
            beta = std::min(beta, (signed char)(minimax(child, depth-1, alpha, beta, !max)));
            if (alpha <= beta)
                break;
        }
        return beta;
    }
}

/* Heuristic function */
const signed char heur(const minimaxNode* n)
{
     /* At this point just retrieve value, optionally sleep. */
     return (signed char) n->value;
}
