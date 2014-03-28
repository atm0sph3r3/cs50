/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    int factor = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    
    //check a positive number was entered
    if(factor <= 0){
        fclose(inptr);
        fprintf(stderr, "A positive number was not entered.");
        return 4; 
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
     // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // padding for output file
    int outPadding = (4 - (bi.biWidth * factor * sizeof(RGBTRIPLE)) % 4) % 4;
 
    // image size
    bi.biSizeImage = ((bi.biWidth * sizeof(RGBTRIPLE) * factor) + outPadding) * (abs(bi.biHeight) * factor);
    
    int originalWidth = bi.biWidth;
    int originalHeight = abs(bi.biHeight);
    
    // image width
    bi.biWidth *= factor;
    
    // image height
    bi.biHeight *= factor;
    
     //Total file size
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // iterate over infile's scanlines
    for (int i = 0; i < originalHeight; i++)
    {
        int isFirst = 1;
    	for(int n = 0; n < factor; n++) {
	        if(!isFirst){
	            fseek(inptr,(-originalWidth * sizeof(RGBTRIPLE)) - padding, SEEK_CUR);
	        } else {
	            isFirst = 0;
	        }
		    
		    // iterate over pixels in scanline
		    for (int j = 0; j < originalWidth; j++)
		    {   
		        // temporary storage
		        RGBTRIPLE triple;

		        // read RGB triple from infile
		        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
		        
		        // write RGB triple to outfile
		        for(int m = 0 ; m < factor; m++) {
	                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
	            }
		            
		    }

		    // skip over padding, if any
		    fseek(inptr, padding, SEEK_CUR);

		    // add appropriate padding to file
		    for (int k = 0; k < outPadding; k++)
		    {
		        fputc(0x00, outptr);
		    }
		}
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
