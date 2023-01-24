#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// function prototyping
int compute_score(string word);
void game_outcome(int score1, int score2);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Prints the game outcome
    game_outcome(score1, score2);
}



// compute_score finds the length of the array the string word. A for-loop goes through all characters
// of the string and adds its respective point to total. total is then returned to main.
int compute_score(string word)
{
    int length = strlen(word);
    int total = 0;

    for (int i = 0; i < length; i++)
    {
        int char_value = word[i];

        if (isupper(word[i]))
        {
            char_value -= 65;
            total += POINTS[char_value];

        }

        else if (islower(word[i]))
        {
            char_value -= 97;
            total += POINTS[char_value];
        }

        else
        {
            break;
        }

    }

    return total;

}



// game_outcome compares score1 & score2 to determine the player with the greater number of points. If
// Player1 & Player2 have the same score, "TIE!" is printed instead.
void game_outcome(int score1, int score2)
{
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }

    if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }

    if (score1 == score2)
    {
        printf("Tie!\n");
    }
}