#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[7];

    // Create array to store plate numbers
    char *plates[8];

    FILE *infile = fopen(argv[1], "r");

    int idx = 0;

    // declares a pointer called temp.
    char *temp = NULL;
    while (fread(buffer, 1, 7, infile) == 7)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // 7 new "spaces of memory" to store each char of 1 plate were created
        // & the pointer temp, points to this.
        temp =  malloc(7 * sizeof(char));

        // This for-loop goes through all the chars in buffer & then stores them
        // in the memory allocated to temp. temp now holds the address to the first char of the plate.
        for (int j = 0; j < 7; j++)
        {
            temp[j] = buffer[j];
        }

        // Now, the address of the 1st char of the plate is assigned to each index of plates.
        plates[idx] = temp;

        // idx is increased by 1, so that it slots the address of the next plate in the next index.
        idx++;
    }

    // this for-loop now prints all 8 plates, through the pointers stored in each index and frees up
    // the memory the pointer is pointing to as it is not required anymore after its printed.
    for (int i = 0; i < idx; i++)
    {
        printf("%s\n", plates[i]);
    }
    
    fclose(infile);
}
