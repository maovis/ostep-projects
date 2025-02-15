#include "reverse.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

int main(int argc, char * argv[]){
	FILE * pF;
	char * line = NULL;
	size_t len = 0;
	ssize_t nread;
	
	sNode * pNodeHead = mallocNode();   // pNodeHead holds the address of HeadNode in heap
	sNode * pNodeTail = pNodeHead;   // at creation time, TailNode coincides with Head Node
	sNode * pNodeCurrent = NULL;   // pNodeCurrent is used as moving cursor to operate on Nodes
	
	printf("\nPoints initial status:\n");
	printf("pNodeHead     : %p\n", pNodeHead);
	printf("pNodeCurrent  : %p\n", pNodeCurrent);
	printf("pNodeTail     : %p\n", pNodeTail);
	printf("- - - - - - - - - - - -\n");

	if (argc < 2){
		printf("to reverse stdin TBD ... \n");
		return 0;
	}
	if (argc > 2){
		printf("deal with more files ?? \n");
		exit(1); // or exit(EXIT_FAILURE); portable
	}
	
	const char * fileName = argv[1]; // argv[1] is the 'file' to reverse
	pF = fopen(fileName, "r");
	if (pF == NULL){   // file pointer validity check
		printf("cannot open file\n");
		exit(1);
	}
	
	setNodeStr(pNodeHead, "_HEAD_", 7); // set _HEAD_ (arbitrary choice^^) to NodeHead->str. 
	
	while ((nread = getline(&line, &len, pF)) != -1){
		/* move Node cursor to TailNode */
		pNodeCurrent = pNodeTail;
		/* add one more Node */
		appendOneNode(pNodeCurrent);  // mallocNode() called here !
		/* move Node cursor to the newly added Node */
		pNodeCurrent = pNodeCurrent->next;
		/* load line (a string) read from file to the newly added Node */
		printf("pNodeCurrent (load string)     : %p\n", pNodeCurrent);
		setNodeStr(pNodeCurrent, line, nread);
		/* move NodeTail to the newly added Node*/
		pNodeTail = pNodeCurrent;
	}
	printNodes(pNodeHead, '>', pNodeTail); // Use '>' or '<' to select display order

	/* free allocated memory */	
	while(pNodeTail != pNodeHead){
		/* move Node cursor to TailNode */
		pNodeCurrent = pNodeTail;
		/* move NodeTail backward*/
		pNodeTail = pNodeTail->prev;
		/* check Node cursor's address */
		printf("pNodeCurrent(free memory)     : %p\n", pNodeCurrent);
		/* free string: memory dynamically allocated in void setNodeStr() */
		freeNodeStr(pNodeCurrent);
		/* free sNode: memory dynamically allocated in void appendOneNode */
		freeNode(&pNodeCurrent);
	};
	
	if(pNodeTail == pNodeHead){
		pNodeTail = NULL;  // Tail rewinds back to Head. Set pNodeTail to NULL, then use the same pNodeHead to free memory
	}else{
		printf("Tail != Head ??\n");
	}
	
	/* free pNodeHead string: memory dynamically allocated in void setNodeStr() */
	freeNodeStr(pNodeHead);
	/* free pNodeHead: memory dynamically allocated in sNode * mallocNode() */
	freeNode(&pNodeHead);
	
	printf("\nPoints end status:\n");
	printf("pNodeHead     : %p\n", pNodeHead);
	printf("pNodeCurrent  : %p\n", pNodeCurrent);
	printf("pNodeTail     : %p\n", pNodeTail);
	printf("- - - - - - - - - - - -\n");
	return 0;
}