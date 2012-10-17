/* Struct of tree of minimax search */
typedef struct minimaxNode 
{
    const signed char value;                  /* Heuristic value or value for heuristic */
    struct minimaxNode* children;             /* Link to the first child */
    const struct minimaxNode* const parent;   /* Link to the parent */
    struct minimaxNode* next;                 /* Link to next sibling */
};

const signed char heur(const minimaxNode* n);
const signed char minimax(const minimaxNode* n, const char depth);
const char * const xmlfilename = "tree.xml";
const minimaxNode* readxmltree(const char* const filename);
const minimaxNode* readxmlnode(const xmlNode* const root,
	                      const minimaxNode* const parent);
