#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

// defining functions called in main.
float calc_hours(int hours[], int weeks, char output);


// main prompts the user for the number of weeks CS50 was taken. Then, it prompts for the hours each week they spent
// on HW. The user can decided whether they want to find the total hours by inputting 'T' or the average using 'A'.
int main(void)
{
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks];

    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }

    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != 'T' && output != 'A');

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}




// calc_hours uses a for loop to calculate the total number of hours. If 'A' is passed in output,
// the average is calculated and returned, otherwise total is returned to main.
float calc_hours(int hours[], int weeks, char output)
{
    float total = 0.0;
    for (int i = 0; i < weeks; i++)
    {
        total += hours[i];
    }

    if (output == 'T')
    {
        return total;
    }

    else
    {
        float average = (total / weeks);
        return average;
    }
}
