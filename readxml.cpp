#include <iostream>           /* For cout and cin */
#include <memory.h>
#include <libxml/parser.h>
#include "readxml.h"

const minimaxNode* readxmltree(const char* const filename)
{
    /* Open XML document */
    xmlDocPtr doc;
    std::cout << "Opening " << filename << "..." << std::endl;
    doc = xmlParseFile(filename);

    if (doc == NULL) 
        std::cerr << "error: could not parse file file.xml" << std::endl;
  
    /* XML root. */
    /*Get the root element node */
    xmlNode *root = NULL;
    root = xmlDocGetRootElement(doc);
  
    /* Must have root element, a name and the name must be "Node" */  
    if( !root || !root->name ||
        xmlStrcmp(root->name, (xmlChar*)("Node")) ) 
    {
        xmlFreeDoc(doc);
        return NULL;
    }
    /* Start recursive treemaking into minimaxNode */
    const minimaxNode* ret = readxmlnode(root, NULL);
    /* Do memory cleanup */
    xmlFreeDoc(doc);
    xmlCleanupParser();
    /* Return Tree */
    return ret;
}

/* Recursive function to create node with n children, pointing to the first
   child, the parent and the right side sibbling. If a certain relative doesn't
   exist, point to NULL. */
const minimaxNode* readxmlnode(const xmlNode* const root, 
                               const minimaxNode* const parent)
{
    minimaxNode *prev_node = NULL, *cur_mm_node = NULL;
    xmlChar *rootvalue = NULL;
    /* Get property value, an integer that is represented by "value" */
    signed char val;
    rootvalue = xmlGetProp(const_cast<xmlNode*>(root), (xmlChar*)("value"));
    val = atoi ((char*)rootvalue);
    
    /* Construct inital Node, with value, and parent. Sibbling and children
       are added later. */
    struct minimaxNode newNode = {val, NULL, NULL};
    
    /* Iterate through children of XML node, which will be children of minimaxNode */
    for(xmlNode *cur_node = root->children; cur_node != NULL; cur_node = cur_node->next)
    {
        /* Make sure this is a Node */
        if ( cur_node->type == XML_ELEMENT_NODE  &&
             !xmlStrcmp(cur_node->name, (const xmlChar*) "Node"))
        {
            /* Recursive call */
            cur_mm_node = const_cast<minimaxNode*>(readxmlnode(cur_node, &newNode));
            /* Have parent point to this new node if it is the first child, 
               otherwise, have previous node point to it as next */
            if (prev_node)
            {
                prev_node->next = cur_mm_node;
            }
            else
            {
                newNode.children = cur_mm_node;
            }
            /* Keep track of previous node */
            prev_node = cur_mm_node;
        }
        
    }
    /* Free memory */
    xmlFree(rootvalue); rootvalue = NULL;
    /* Move node to Heap */
	struct minimaxNode* ret = (minimaxNode*) malloc(sizeof(struct minimaxNode));
	memcpy(ret, &newNode, sizeof(struct minimaxNode));
	/* Return Node */
    return ret;
}
