#include <cs50.h>
#include <stdio.h>


// defining functions called in main
int get_start_size(void);
int get_end_size(int start_size);
int find_threshold(int current_size, int end_size);

int main(void)
{
    // Prompt for start size
    int start_size = get_start_size();

    // Prompt for end size
    int end_size = get_end_size(start_size);

    // Calculate number of years until we reach threshold
    int years_till_threshold = find_threshold(start_size, end_size);

    // Print number of years
    printf("Years: %i\n", years_till_threshold);
}



// Returns the start_size of the population ensuring the user inputs a value > 9
int get_start_size(void)
{
    int user_input;
    do
    {
       user_input= get_int("What is the start size of the population?: ");
    }
    while (user_input < 9);
    return user_input;
}



// Returns the end_size of the population ensuring the user inputs a value > start_size
int get_end_size(int start_size)
{
    int user_input;
    do
    {
       user_input = get_int("What is the end size of the population?: ");
    }
    while (user_input < start_size);
    return user_input;
}



// Assigns start_size to current_size and a new variable n, denoting the number of years is
// is assigned the int value of 0. The while loop goes evaluates the expression assigning the
// new current_size of the population at the nth year. n is increased by 1 each loop. If the
// current size is equal to the end size, n is returned.
int find_threshold(int current_size, int end_size)
{
    int n = 0;

    while (current_size < end_size)
    {
        current_size = (current_size) + (current_size / 3) - (current_size / 4);
        n += 1;

    }
    return n;
}
