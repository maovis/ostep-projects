#ifndef REVERSE_H
#define REVERSE_H

#include <stdlib.h> // define type 'size_t'

/** type sNode: Node of a doubly linked list **/
typedef struct Node { 
	char * str; 
	struct Node * next; // Pointer to next node in DLL 
	struct Node * prev; // Pointer to previous node in DLL 
} sNode;

/** return a sNode pointer with allocated memory in heap **/
sNode * mallocNode();

/** free the memory allocated by pointer sNode->str **/
void freeNodeStr(sNode * pNode);

/** free the memory allocated by pointer sNode **/
void freeNode(sNode ** const ppNode);

/** allocate memory for pNode->str in heap **/
void setNodeStr(sNode * const pNode, const char * strIn, const size_t strInLen);

/** append one more sNode after the input sNode  **/
void appendOneNode(sNode * const pNode);

/** print variables' address and content within a sNode **/
void printNodeInfo(const sNode * const pNode);

/** print Nodes info Head > Tail or Tail < Head **/
void printNodes(sNode * const pHead, const char direction, sNode * const pTail);

#endif /* REVERSE_H */