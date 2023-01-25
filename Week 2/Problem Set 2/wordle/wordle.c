#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// each of our text files contains 1000 words
#define LISTSIZE 1000

// values for score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN   "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW  "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED     "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET   "\e[0;39m"

// user-defined function prototypes
string get_guess(int wordsize);
int check_word(string guess, int wordsize, int status[], string choice);
void print_word(string guess, int wordsize, int status[]);
void game_outcome(bool won, string choice);



// main uses a Command-Line Argument to determine the word length used for the wordle game. If the user does not enter
// a word length value, main returns 1 and a error message is printed. Else, the game of wordle continues, giving the user
// word length + 1 tries to guess the word. If the user is unable to guess the word, the target word, along with some text
// is printed onto the screen.
int main(int argc, string argv[])
{
    if ((argc <= 1) || (argc > 2))
    {
        printf("Usage ./wordle wordsize\n");
        return 1;
    }

    int wordsize = 0;
    int number = atoi(argv[1]);


    if ((number <= 4) || (number > 8))
    {
        printf("Error: wordsize must be either 5, 6, 7 or 8\n");
        return 1;
    }

    wordsize = number;

    char wl_filename[6];
    sprintf(wl_filename, "%i.txt", wordsize);
    FILE *wordlist = fopen(wl_filename, "r");

    if (wordlist == NULL)
    {
        printf("Error opening file %s.\n", wl_filename);
        return 1;
    }

    // load word file into an array of size LISTSIZE
    char options[LISTSIZE][wordsize + 1];

    for (int i = 0; i < LISTSIZE; i++)
    {
        fscanf(wordlist, "%s", options[i]);
    }

    // pseudorandomly select a word for this game
    srand(time(NULL));
    string choice = options[rand() % LISTSIZE];

    // allow one more guess than the length of the word
    int guesses = wordsize + 1;
    bool won = false;

    // print greeting, using ANSI color codes to demonstrate
    printf(GREEN"This is WORDLE50"RESET"\n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of\n", guesses, wordsize);

    // main game loop, one iteration for each guess
    for (int i = 0; i < guesses; i++)
    {
        // obtain user's guess
        string guess = get_guess(wordsize);

        // array to hold guess status, initially set to zero
        int status[wordsize];

        // set all elements of status array initially to 0, aka WRONG
        for (int j = 0; j < wordsize; j++)
        {
            status[i] = 0;
        }

        // Calculate score for the guess
        int score = check_word(guess, wordsize, status, choice);

        printf("Guess %i: ", i + 1);

        // Print the guess
        print_word(guess, wordsize, status);

        // if they guessed it exactly right, set terminate loop
        if (score == EXACT * wordsize)
        {
            won = true;
            break;
        }
    }

    // Print the game's result
    game_outcome(won, choice);
    // that's all folks!
    return 0;
}




string get_guess(int wordsize)
{
    string guess = "";

    // ensure users actually provide a guess that is the correct length
    do
    {
        guess = get_string("Input a %i-letter word: ", wordsize);
    }
    while (strlen(guess) != wordsize);
    return guess;
}



// check_word uses a for-loop, looping through each letter in the word. This letter is then compared to the target letter,
// if the letter is correct, 1 point is awarded & in the right place as well, 2 points are awarded. The total points are assigned
// to score uses a for-loop on status, an array of these points which is then returned to main.
int check_word(string guess, int wordsize, int status[], string choice)
{
    int score = 0;

    // compare guess to choice and score points as appropriate, storing points in status
    for (int i = 0; i < wordsize; i++)
    {
        char guess_letter = guess[i];

        for (int j = 0 ; j < wordsize; j++)
        {
            char choice_letter = choice[j];

            if ((i == j) && (choice_letter == guess_letter))
            {
                status[i] = EXACT;
                break;
            }

            else if (choice_letter == guess_letter)
            {
                status[i] = CLOSE;
            }

        }
    }

    for (int k = 0; k < wordsize; k++)
    {
        score += status[k];
    }

    return score;
}



// print_word uses a for-loop to go through each letter in the word, changing its color depending on the points
// it has.
void print_word(string guess, int wordsize, int status[])
{
    for (int i = 0; i < wordsize; i++)
    {
        if (status[i] == 2)
        {
            printf(GREEN"%c"RESET"", guess[i]);
        }

        else if (status[i] == 1)
        {
            printf(YELLOW"%c"RESET"", guess[i]);
        }

        else
        {
            printf(RED"%c"RESET"", guess[i]);
        }

    }

    printf("\n");
    return;
}




// game_outcome prints whether the user has won or lost. The target word is also printed if the user lost the game.
void game_outcome(bool won, string choice)
{
    if (won == true)
    {
        printf("You won!\n");
    }

    else
    {
        printf("You lost! The word was %s.\n", choice);
    }
}