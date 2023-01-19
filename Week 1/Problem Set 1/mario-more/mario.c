#include <cs50.h>
#include <stdio.h>


// defining functions called in main
int user_height(void);
void draw_pyramids(int height);
void print_row(int height, int i);


// main gets the user height and prints the pyramids of desired height.
int main(void)
{
    int height = user_height();
    draw_pyramids(height);
}



// user_height assigns the height to input, provided 1 <= input <=8 and returns to main.
int user_height(void)
{
    int input;
    do
    {
        input = get_int("Height: ");
    }
    while ((input < 1) || (input > 8));
    return input;
}


// draw_pyramids draws the pyramids by using a for loop that prints each row of the two pyramids. i is increased by
// one to prevent an empty row from being drawn.
void draw_pyramids(int height)
{
    for (int i = 0; i < height; i++)
    {
        print_row(height, i + 1);
    }
}


// print_row prints the spaces, and then prints the #. A space is then added. The process is then repeated,
// printing the #s for the second pyramid. The \n creates a new line for the next row to be printed into the terminal.
void print_row(int height, int i)
{

    int spaces_req = (height - i);


    for (int j = 0; j < (spaces_req); j++)
    {
        printf(" ");
    }

    for (int j = 0; j < (i); j++)
    {
        printf("#");
    }


    printf("  ");


    for (int k = 0; k < (i); k++)
    {
        printf("#");
    }


    printf("\n");



}