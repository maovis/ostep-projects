#include "reverse.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

/** type sNode: Node of a doubly linked list **/
/** defined in reverse.h **/

/** return a sNode pointer with allocated memory in heap **/
sNode * mallocNode(){
	sNode * pNode = (sNode *) malloc(sizeof(sNode));
	pNode->str = NULL;
	pNode->next = NULL;
	pNode->prev = NULL;
	return pNode;
}

/** free the memory allocated by pointer sNode->str **/
void freeNodeStr(sNode * pNode){
	free(pNode->str);
	pNode->str = NULL;
}

/** free the memory allocated by pointer sNode **/
void freeNode(sNode ** const ppNode){  // if use sNode * pNode, cannot set pNode = NULL
	assert((*ppNode)->str == NULL); // check pNode->str has been freed
	free(*ppNode);  // free pNode
	*ppNode = NULL;  // dereferencing ppNode => pNode
}

/** allocate memory for pNode->str in heap **/
void setNodeStr(sNode * const pNode, const char * strIn, const size_t strInLen){
	pNode->str = (char *) malloc(strInLen);
	strcpy(pNode->str, strIn);
}

/** append one more sNode after the input sNode  **/
void appendOneNode(sNode * const pNode){
	assert(pNode->next == NULL); // verify pNode has no subsequent sNode
	sNode * pNewNode = mallocNode();
	pNewNode->prev = pNode;  // link back newNode to pNode
	pNode->next = pNewNode;  // link forward pNode to newNode
}

/** print variables' address and content within a sNode **/
void printNodeInfo(const sNode * const pNode){
	printf("-------------\n| Node info | \n-------------\n");
	printf("pNode       &: %p\n", pNode);
	printf("pNode->str  &: %p    *: %p\n", &(pNode->str), pNode->str);
	printf("pNode->next &: %p    *: %p\n", &(pNode->next), pNode->next);
	printf("pNode->prev &: %p    *: %p\n", &(pNode->prev), pNode->prev);
	printf("pNode->str   : %s\n", pNode->str);
	printf("----\n");
}

/** print Nodes info Head > Tail or Tail < Head **/
void printNodes(sNode * const pHead, const char direction, sNode * const pTail){
	sNode * pCurrent;
	
	assert(pHead->prev == NULL);
	assert(pTail->next == NULL);
	if(direction == '>'){
		printf("Print Nodes Head > Tail:\n\n");
		pCurrent = pHead;
		do {
			printNodeInfo(pCurrent);
			pCurrent = pCurrent->next;
		} while(pCurrent != NULL);
		printf("\n");		
	} else if(direction == '<'){
		printf("Print Nodes Tail > Head:\n\n");
		pCurrent = pTail;
		do {
			printNodeInfo(pCurrent);
			pCurrent = pCurrent->prev;
		} while(pCurrent != NULL);
		printf("\n");			
	}
	else{
		printf("Use '>' or '<' to select print order\n\n");
	}
}