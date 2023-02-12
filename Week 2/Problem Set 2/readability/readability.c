#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// function prototyping
float find_total_letters(string text);
float find_total_words(string text);
float find_total_sentences(string text);
void print_grade(int cl_index);



// main takes in the user's text. It then finds the total letters, words & sentences in the text. It then uses the Coleman-Liau index,
// to determine the grade. The grade is then printed.
int main(void)
{
    string user_text = get_string("Text: ");

    float total_letters = find_total_letters(user_text);
    float total_words = find_total_words(user_text);
    float total_sentences = find_total_sentences(user_text);

    float l = (total_letters / total_words) * 100;
    float s = (total_sentences / total_words) * 100;

    int cl_index = (0.0588 * l - 0.296 * s - 15.8) + 0.5;

    print_grade(cl_index);

}



// find_total_letters find the total number of letters by finding the total number alphabetical characters, this total is then returned to main.
float find_total_letters(string text)
{
    int length = strlen(text);
    float total = 0;
    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]))
        {
            total += 1.0;
        }

    }
    return total;

}



// find_total_words find the total number of words by finding the total number of spaces and adding this total by one (fencepost problem),
// this total is then returned to main.
float find_total_words(string text)
{
    int length = strlen(text);
    float total = 0;
    for (int i = 0; i < length; i++)
    {
        if (text[i] == ' ')
        {
            total += 1.0;
        }

    }
    return (total + 1.0);

}



// find_total_sentences find the total number of letters by finding the total number of '.', '!' & '?' this total is then returned to main.
float find_total_sentences(string text)
{
    int length = strlen(text);
    float total = 0;
    for (int i = 0; i < length; i++)
    {
        if ((text[i] == '.') || (text[i] == '!') || (text[i] == '?'))
        {
            total += 1.0;
        }

    }
    return total;

}



// print_grade prints the respective grade. If Grade <= 1 or Grade >= 16, "Before Grade 1" "Grade 16+" is printed to the terminal. Else the Grade is then printed.
void print_grade(int cl_index)
{


    if (cl_index >= 16)
    {
        printf("Grade 16+\n");
    }

    else if (cl_index <= 1)
    {
        printf("Before Grade 1\n");
    }

    else
    {
        printf("Grade %i\n", cl_index);
    }
}