#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ENTRYSIZE 5

bool openAndPrint(int argc, char * argv[]);
void unzipFiveByteEntry(char singleEntry[ENTRYSIZE]);

int main(int argc, char * argv[]){

	if (argc < 2){
		printf("wunzip: file1 [file2 ...]\n");
		exit(1); // or exit(EXIT_FAILURE); portable
	} else {
		if(!openAndPrint(argc, argv)){
			exit(1);
		}
	}
	return 0;
}

bool openAndPrint(int argc, char * argv[]){
	int filec = argc-1;  // -1: substruct the 1st argument "./unwzip"
	FILE * pF[filec];  // array of file stream
	char entry[ENTRYSIZE];
	
	for(size_t i=0; i<filec; ++i){
		const char * fileName = argv[i+1];
		pF[i] = fopen(fileName, "r");
		if (pF[i] == NULL){   // file pointer validity check
			printf("wunzip: cannot open file\n");
			return false;
		}
		/* attempt to read 1 block of 5 bytes each time*/
		while (fread(entry, ENTRYSIZE, 1, pF[i]) == 1){
			unzipFiveByteEntry(entry);
		}
		fclose(pF[i]);   // close current file
	}   // go over input files
	return true;
}

void unzipFiveByteEntry(char singleEntry[ENTRYSIZE]){
	/**
	Each entry is comprised of a 4-byte integer (the run length) and the single character.
	**/
	char character;
	unsigned int count = 0;

	count +=  singleEntry[0];
	count += (singleEntry[1] << 8);
	count += (singleEntry[2] << 16);
	count += (singleEntry[3] << 24);
	character = singleEntry[4];
	for (size_t i=0; i<count; ++i){
		printf("%c", character);
	}
}