#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// vote goes through the whole array, candidates[], if the name of the candidate is present,
// the votes of the candidate (int type) is increased by 1.
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!(strcmp(candidates[i].name, name)))
        {
            candidates[i].votes += 1;
            return true;
        }

    }
    return false;
}

// print_winner finds the max_votes amongst all the candidates using a for-loop. Then, another
// for-loop is used to print out all the candidates (in the event of a tie) with the same number
// of votes as max_votes.
void print_winner(void)
{
    int max_votes = 0;
    for (int i = 0; i < candidate_count; i++)
    {

        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }

    }


    for (int k = 0; k < candidate_count; k++)
    {
        if (candidates[k].votes == max_votes)
        {
            printf("%s\n", candidates[k].name);
        }
    }


    return;
}