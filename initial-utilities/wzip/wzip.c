#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ENTRYSIZE 5

bool openAndWrite(int argc, char * argv[], FILE * pFileOut);
void fillFiveByteEntry(char singleEntry[ENTRYSIZE], unsigned int count, char character);

int main(int argc, char * argv[]){
	FILE * pFout;
	if (argc < 2){
		printf("wzip: file1 [file2 ...]\n");
		exit(1); // or exit(EXIT_FAILURE); portable
	} else {
		pFout = fopen("out.z", "w");
		if(!openAndWrite(argc, argv, pFout)){
			exit(1);
		}
		fclose(pFout);
	}
	return 0;
}

bool openAndWrite(int argc, char * argv[], FILE * pFileOut){
	int filec = argc-1;  // -1: substruct the 1st argument "./wzip"
	FILE * pF[filec];  // array of file stream
	char entry[ENTRYSIZE];
	char curCh = '\0';
	char preCh = '\0';
	unsigned int counter = 0;
	
	for(size_t i=0; i<filec; ++i){
		const char * fileName = argv[i+1];
		pF[i] = fopen(fileName, "r");
		if (pF[i] == NULL){   // file pointer validity check
			printf("wzip: cannot open file\n");
			return false;
		}
		while((curCh = fgetc(pF[i])) != EOF){ // get 'char' to the end of the file
			if(curCh == preCh){  // read the same char in a row
				++counter;
			} else{   // read a diff char
				if(counter > 0){   // write down the run-length encoding of the previous char
					fillFiveByteEntry(entry, counter, preCh);
					fwrite(entry, ENTRYSIZE, 1, pFileOut);
					fwrite(entry, ENTRYSIZE, 1, stdout);
				}
				preCh = curCh;   // use current char for 
				counter = 1;   // curent char already occurs once
			}
		}
		fclose(pF[i]);   // close current file
	}   // go over input files
	// write down the ongoing char
	fillFiveByteEntry(entry, counter, preCh);
	fwrite(entry, ENTRYSIZE, 1, pFileOut);
	fwrite(entry, ENTRYSIZE, 1, stdout);	
	return true;
}

void fillFiveByteEntry(char singleEntry[ENTRYSIZE], unsigned int count, char character){
	/**
	Each entry is comprised of a 4-byte integer (the run length) and the single character.
	**/
	singleEntry[0] =  (count & 0x000000FF);
	singleEntry[1] = ((count & 0x0000FF00) >> 8);
	singleEntry[2] = ((count & 0x00FF0000) >> 16);
	singleEntry[3] = ((count & 0xFF000000) >> 24);
	singleEntry[4] = character;
}