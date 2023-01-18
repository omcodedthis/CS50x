#include <cs50.h>
#include <stdio.h>

bool prime(int number);

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

bool prime(int number)
{
    // divides number with all integers starting from 2,
    // if the int and the float of remainder are not equal, it means that
    // there is a remainder as the int value truncates the decimals, thus
    // number is not prime and the boolean false is returned.
    for (int test = 2; test < number; test++)
    {
        int remainder = (number / test);
        float remainder2 = ((float) number / (float) test);
        if (remainder == remainder2)
        {
            return false;
        }
    }
    return true;
}