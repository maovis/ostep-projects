#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFERSIZE 255

bool openAndPrint(const char * fileName, const char * term); // return false if cannot open file

int main(int argc, char * argv[]){

	if (argc < 2){
      printf("wgrep: searchterm [file ...]\n");
      exit(1); // or exit(EXIT_FAILURE); portable
   } else {
		const char * term = argv[1]; // argv[1] is the 'term' to search
		if(argc == 2){ // a search term, but no file, is specified
			char buffer[BUFFERSIZE];
			while(fgets(buffer, BUFFERSIZE, stdin) != NULL){ // wgrep should read from standard input
				if (strstr(buffer, term) != NULL) {
					printf("%s", buffer);
				} 
			}			
		} else{
			for(size_t i=2;i<argc;++i){
				if(!openAndPrint(argv[i], term)) exit(1);
			}
		}
	}
	return 0;
}

bool openAndPrint(const char * fileName, const char * term){
	FILE * pF;
	char * line = NULL;
	size_t len = 0;
   ssize_t nread;
	
	pF = fopen(fileName, "r");
	if (pF == NULL){
		printf("wgrep: cannot open file\n");
		return false;
	}
	while ((nread = getline(&line, &len, pF)) != -1){
		if (strstr(line, term) != NULL) {
			printf("%s", line);
		} 
   }
	fclose(pF);	
	return true;
}


