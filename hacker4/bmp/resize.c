/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
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
        printf("Usage: ./resize f infile outfile\n");
        return 1;
    }

    // Check factor
    int resizeFactor = atoi(argv[1]);
    if (!(resizeFactor < 101 && resizeFactor > 0))
    {
        printf("The factor is not quite right: %i \n", resizeFactor);
        return 1;
    }

    // remember filenames
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

    BITMAPFILEHEADER bfOut = bf;
    BITMAPINFOHEADER biOut = bi;

    // determine image size in pixels
    biOut.biWidth *= resizeFactor;
    biOut.biHeight *= resizeFactor;

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingOut =  (4 - (biOut.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine image size in bytes
    biOut.biSizeImage = abs(biOut.biWidth * biOut.biHeight * 3 ) + abs(biOut.biHeight * paddingOut);
    bfOut.bfSize = 54 + biOut.biSize;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfOut, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biOut, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    int ireloop = 1;
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++, ireloop++)
    {

        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile resizeFactor times
            for (int k = 0; k < resizeFactor; k++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }

        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < paddingOut; k++)
        {
            fputc(0x00, outptr);
        }

        if (ireloop < resizeFactor)
        {
            i--;
            fseek(inptr, -((int) (bi.biWidth * sizeof(RGBTRIPLE) + padding)), SEEK_CUR);
        } else 
        {
            ireloop = 0;
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
