#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

//function prototyping
int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

// convert uses a recursion. Firstly, the base case is when the length of the string passed to input is 0, ending the loop of recursion.
// The recursion goes all the way back till the first integer. Then, it "unravels". The final call of convert(input) evaluates to the first
// number. This number is subsequently multiplied by 10 and added onto the next number (tens ones place etc). After it fully "unravels",
// the final integer value is then returned to the first call of convert(input) which was in main. All the but the final return statement,
// evaluate to an int in the convert(input) function.
int convert(string input)
{
    int integer = 0;
    int length = strlen(input);
    if (length == 0)
    {
        return integer;
    }

    integer = input[length - 1] - 48;
    input[length - 1] = '\0';
    return integer + 10 * convert(input);
}