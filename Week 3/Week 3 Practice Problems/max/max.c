// Practice writing a function to find a max value

#include <cs50.h>
#include <stdio.h>

int max(int array[], int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Number of elements: ");
    }
    while (n < 1);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = get_int("Element %i: ", i);
    }

    printf("The max value is %i.\n", max(arr, n));
}

// max_value uses a bubble sort to sort the array in ascending order. The max value is returned after the first pass if
// the user has already sorted the values. Else, the array is sorted and the max value (final element in array) is returned
// to main.
int max(int array[], int n)
{
    int swaps = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                int value_swapper = array[j];
                array[j] = array[j + 1];
                array[j + 1] = value_swapper;
            }
        }
        if (swaps == 0)
        {
            return array[n - 1];
        }
    }


    return array[n - 1];
}
