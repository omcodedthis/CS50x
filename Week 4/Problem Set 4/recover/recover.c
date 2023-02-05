#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


// defining a constant & renaming uint8_t to BYTE
const int JPEG_BLOCK = 512;
typedef uint8_t BYTE;

// function prototyping
int is_jpeg_header(int size, BYTE buffer[]);


// main ensures that only 1 CLA is entered. Then it takes the .raw file and retrieves each jpeg's
// data and creates a new jpeg using this data. This is done for all jpeg files in the file.
int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *infile = fopen(argv[1], "r");

    BYTE holder[JPEG_BLOCK];
    char *filename = malloc(sizeof(char) * 8);
    FILE *img = NULL;
    int total_jpegs = 0;
    int found_first = 0;

    while (fread(holder, 1, JPEG_BLOCK, infile) == JPEG_BLOCK) // want blocks of 512, no less
    {

        if (is_jpeg_header(JPEG_BLOCK, holder))
        {

            if (total_jpegs == 0)
            {
                found_first = 1;
                sprintf(filename, "%03i.jpg", total_jpegs);
                img = fopen(filename, "w");
                fwrite(holder, JPEG_BLOCK, 1, img);
                total_jpegs++;
                continue; //prevent bottom if statement from occuring

            }

            if (total_jpegs > 0)
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", total_jpegs);
                img = fopen(filename, "w");
                fwrite(holder, JPEG_BLOCK, 1, img);
                total_jpegs++;
            }
        }

        else
        {
            if (found_first == 1)
            {
                fwrite(holder, JPEG_BLOCK, 1, img);
                continue;
            }

            else
            {
                continue;
            }
        }
    }

    fclose(img);
    fclose(infile);
    free(filename);
    return 0;






}




// is_jpeg_header checks whether this 512 byte chunk is the start of a jpeg file by checking
// for a jpeg header. If it is found, 1 is returned.
int is_jpeg_header(int size, BYTE buffer[])
{
    if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
    {
        return 1;
    }

    else
    {
        return 0;
    }
}