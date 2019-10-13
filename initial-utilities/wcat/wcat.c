#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool openAndPrint(const char * fileName); // return false if cannot open file

int main(int argc, char * argv[]){
	
	if (argc < 2){
		//printf("missing fileName\n");
		return (0);
	} else {
		for(int i=1;i<argc;++i){
			if(!openAndPrint(argv[i])) exit(1);
		}
	}
   return (0);
}

bool openAndPrint(const char * fileName){
	FILE * pF;
	char buffer[255];
	
	pF = fopen(fileName, "r");
	if (pF == NULL){
		printf("wcat: cannot open file\n");
		return false;
	}
	while(fgets(buffer, 255, pF) != NULL){
		printf("%s", buffer);
	}
	fclose(pF);	
	return true;
}