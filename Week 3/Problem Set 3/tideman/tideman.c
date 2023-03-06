#include <cs50.h>
#include <stdio.h>
#include <string.h>
// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_cycle(int end, int cycle_start);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// vote uses a for-loop to check whether the name inputted by the user is present in the
// candidates array. Then, it adds it to the rank array, indexed in order of preference,
// returning true. Else, false is returned and the vote is considered invalid.
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!(strcmp(name, candidates[i])))
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// record_preferences takes in the ranks array and assorts the votes into a 2D array, where i,
// a candidate is compared in terms of their preference to another candidate, j.
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {

            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// add_pairs, add the pairs of preferences into the array pairs. For the cases of comparing the
// same candidate, the loop is broken. If the number of voters who prefer candidate i over
// candidate j is greater than the reverse of this case, the pair is added to pairs, where the
// winner the candidate with higher preference of themselves to another candidate. This logic
// applies to the case where number of voters who prefer candidate j to candidate i. The pair_count
// is then increased as the size of the pairs array is increased to add the incoming pair. This
// variable also acts as a counter to correctly index the pair added (add it right after the prev
// pair).
void add_pairs(void)
{

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {

            if (i == j)
            {
                break;
            }

            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }

            if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }


        }
    }

    return;
}

// sort_pairs uses a Bubble Sort to sort the pairs in increasing order of victory, determined
// by the margin of votes between the two candidates. This does not affect the lock_pairs function
// as the locked pairs would just be added in reverse without affecting the outcome of the winning candidate.
void sort_pairs(void)
{
    int swaps = 0;
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count - 1; j++)
        {
            if ((pairs[j].winner - pairs[j].loser) > (pairs[j + 1].winner - pairs[j + 1].loser))
            {
                pair temp = pairs[j];
                pairs[j] = pairs [j + 1];
                pairs[j + 1] = temp;
                swaps += 1;

            }
        }

        if (swaps == 0)
        {
            return;
        }

    }
    return;
}

// lock_pairs locks the pairs into a graph. While ensuring a cycle (closed cycle of no definitive
// winner, like rock, paper & scissors) between the candidates does not occur, the pairs are
// locked into place (i over j), evaluating to true (candidate i wins when compared to
// candidate j), creating a 2D boolean array. The default for each element in the array is false.
void lock_pairs(void)
{

    for (int i = 0; i < pair_count; i++)
    {

        if (!(check_cycle(pairs[i].loser, pairs[i].winner)))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }


    }
    return;
}

// print_winner prints the winner by determining the candidate where no other candidate is
// preferred to them, denoted by false. The candidate with the same number of "false" elements
// as the candidate_count is then crowned the winner of the election.
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int win = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (!(locked[j][i]))
            {
                win++;
            }


            if (win == candidate_count)
            {
                printf("%s\n", candidates[i]);
            }
        }
    }
    return;
}

// check_cycle checks whether a cycle is formed before slotting the pairs into the graph. If the end is equal to the
// start, true is returned. Else, the for-loop checks for the other candidates and if a cycle is found true is returned.
// Only when both of these, do not yield a true value, false is returned.
bool check_cycle(int final, int start)
{
    if (start == final)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {

        if (locked[final][i])
        {
            if ((check_cycle(i, start)))
            {
                return true;

            }
        }

    }

    return false;
}