#include <cs50.h>
#include <stdio.h>

bool prime(int number);


// main gets the min and max numbers from the user. A for loop checks every integer
// within this range to check for prime numbers. The prime numbers are then printed to
// the terminal.
int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}


// prime divides the number with all integers starting from 2 up to number. If there no
// remainder from integer, means number is divisible by test and thus is not prime,
// returning false. If for all values of test remainder is not 0, means it is prime.
bool prime(int number)
{

    for (int test = 2; test < number; test++)
    {
        int remainder = number % test;
        if (remainder == 0)
        {
            return false;
        }
    }
    return true;
}