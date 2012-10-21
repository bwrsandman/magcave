#include <algorithm>          /* For std::max */
#include <iostream>           /* For cout and cin */
#include <unistd.h>           /* For sleep */
#include "minimax.h"
#include "readxml.h"

int main(int argc, char * argv[])
{
    /* Load minimax tree from xml file. */
    const minimaxNode* n = readxmltree(xmlfilename);
    /* Perform minimax, print result. */
    std::cout << int(minimax(n, 7)) << std::endl;
    return 0;
}

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
     sleep(0.2);
     return (signed char) n->value;
}
