// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // This section creates an array for store the 44 bytes header of the infile. This array
    // is then used to write this data to the output file.
    uint8_t header[HEADER_SIZE];
    fread(&header, HEADER_SIZE, 1, input);
    fwrite(&header, HEADER_SIZE, 1, output);

    // buffer is a variable that store each of the 2 byte audio sample. The while-loop loops
    // throughout the infile, storing the sample in buffer. buffer is then multiplied by 2 &
    // assigned back to buffer. buffer is then used to write the edited audio sample to the
    // outfile.
    int16_t buffer;
    while (fread(&buffer, 2, 1, input)) // LP
    {
        buffer *= factor;
        fwrite(&buffer, 2, 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}
