/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 *	0xff 0xd8 0xff 0xe0
 *	0xff 0xd8 0xff 0xe1
 
 * Recovers JPEGs from a forensic image.
 */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t  BYTE;

typedef struct{
	BYTE byteOne;
	BYTE byteTwo;
	BYTE byteThree;
	BYTE byteFour;	
} __attribute__((__packed__))  
JPEG;

bool check(JPEG* test);
void switchBytes(JPEG* test, BYTE* newByte);

int main(int argc, char* argv[]) {
    FILE* file = fopen("card.raw", "r");
    FILE* outfile = NULL;
    JPEG test;
    bool isFile = false;
    int counter = 0;
    char filename[8];
    BYTE nextByte;
    
    // ensure file opened before proceeding
    if(!file){	
		fprintf(stderr,"Unable to open file.");
		return 1;
	} else {
		//read in four bytes to initially fill JPEG
		fread(&test,sizeof(JPEG),1,file);

		while(true){
			//get next byte
		    nextByte = (BYTE)fgetc(file);
			
			if(feof(file) == 0 && ferror(file) == 0 && counter <= 50){
				//test whether the pattern starting a JPEG has been found
				if(check(&test)){
					//process current file
					isFile = true;
					if(outfile != NULL) {
						fclose(outfile);
					}
					//generate new file name for outfile
					sprintf(filename,"%03i.jpg",counter);
					//open new file for writing
					outfile = fopen(filename,"w");
					//write first four bytes to file
					fwrite(&test.byteOne,sizeof(BYTE),1,outfile);
					//increase counter
					++counter;
				} else if(isFile) {
					fwrite(&test.byteOne, sizeof(BYTE),1,outfile);
				}
				
		        //shift bytes in JPEG by one
		        switchBytes(&test,&nextByte);
			} else {
				//close current file and break out of loop
				if(outfile != NULL) {
				    fwrite(&test,sizeof(JPEG),1,outfile);
					fclose(outfile);
				}
				break;
			}
		}
	}
    return 0;
}

bool check(JPEG* test){
	if(test->byteOne == 0xFF && test->byteTwo == 0xD8 && test->byteThree == 0xFF && (test->byteFour == 0xE1 || test->byteFour == 0xE0)){
		return true;
	} else {
		return false;
	}
}

void switchBytes(JPEG* test, BYTE* newByte){
	test->byteOne = test->byteTwo;
	test->byteTwo = test->byteThree;
	test->byteThree = test->byteFour;
	test->byteFour = *newByte;
}
