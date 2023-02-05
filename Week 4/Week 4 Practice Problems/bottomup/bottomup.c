// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: copy infile outfile\n");
        return 1;
    }

    // Remember filenames
    char *infile = argv[1];
    char *outfile = argv[2];

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // Open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 3;
    }

    // Read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        printf("Unsupported file format.\n");
        return 4;
    }
// This is what was changed! According to BITMAPINFOHEADER's MSFT info, "If biHeight is
// negative, the bitmap is a top-down DIB and its origin is the upper-left corner." This
// means that the picture starts from the top-left corner, and each pixel's location
// is indexed in a top-down formation (upright). Since the original picture was a bottom-
// up, this value had to be reversed before it was written to the outfile (og image was
// was changed and then this info was read to the outfile). The main mistake I made was
// I kept DEFINING THE TYPE of bi.biHeight w/o realising that when you do that you are
// REDEFINING & not editing the original bi.biHeight of the infile. DWORD, is a type similar
// to an int.
    bi.biHeight = -1 * bi.biHeight;

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // Iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // Temporary storage
            RGBTRIPLE triple;

            // Read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // Write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // Skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // Then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // Close infile
    fclose(inptr);

    // Close outfile
    fclose(outptr);

    // Success
    return 0;
}
