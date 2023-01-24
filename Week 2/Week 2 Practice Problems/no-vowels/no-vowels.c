// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// function prototyping
void make_leetspeak(string word);


// main takes in a Command-Line Argument and if the total arguments (argc) is less than 1 or greater 2,
// meaning multiple or no CLAs have been entered, a error code is printed and main returns a value of 1.
// Else, arg[1], the word is assigned to the variable word. word is then converted to leetspeak using
// make_leetspeak. word is then printed.
int main(int argc, string argv[])
{
    if ((argc <= 1) || (argc > 2))
    {
        printf("Usage ./no-vowels word\n");
        return 1;
    }

    string word = argv[1];

    make_leetspeak(word);

    printf("%s \n", word);
}



// make_leetspeak finds the length of the string using strlen. The for-loop goes through all the characters
// in word, switching the vowels with numbers using the switch statement. Since strings in C are are arrays
// chars, a return statement is not required.
void make_leetspeak(string word)
{
    int length = strlen(word);
    for (int i = 0; i < length; i++)
    {
        switch (word[i])
        {
            case (('a') | ('A')):
                word[i] = '6';
                break;

            case (('e') | ('E')):
                word[i] = '3';
                break;

            case (('i') | ('I')):
                word[i] = '1';
                break;

            case (('o') | ('O')):
                word[i] = '0';
                break;

            default:
                break;
        }

    }
}