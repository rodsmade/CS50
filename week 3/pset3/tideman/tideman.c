#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j >> i wins over j and this arrow does not create a cycle
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
pair pairs[MAX * (MAX - 1) / 2];    // one half of square matrix sans main diagonal, NOT actual amount of pairs.

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

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

// Update ranks given a new vote
// OK
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(candidates[i], name))
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int rank_pivot = 0; rank_pivot < candidate_count - 1; rank_pivot++)
    {
        for (int rank_below = rank_pivot + 1; rank_below < candidate_count; rank_below++)
        {
            preferences[ ranks[rank_pivot] ][ ranks[rank_below] ]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 1; i < candidate_count; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (preferences[i][j] != preferences[j][i])
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                }
                else
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                }
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int strength[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        strength[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }
    // Sorts array of pairs based off array of strengths
    // is this a bubble sort
    pair aux;
    for (int i = 1; i < pair_count; i++)
    {
        if (strength[i] > strength[i - 1])
        {
            aux = pairs[i - 1];
            pairs[i - 1] = pairs[i];
            pairs[i] = aux;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // locks the pair in first anyways and then checks if it creates a cycle
        locked[ pairs[i].winner ][ pairs[i].loser ] = true;
        // checks if it created a cycle. A cycle means there's no source, i.e., there are no columns with only false values on it left
        // if that's the case, it rolls back (turns true back to false) and discards the pair, moving forward
        int count_truths = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            for (int k = 0; k < candidate_count; k++)
            {
                if (locked[k][j] == true)
                {
                    count_truths++;
                    k = candidate_count;
                }
            }
        }
        if (count_truths == candidate_count)
        {
            locked[ pairs[i].winner ][ pairs[i].loser ] = false;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int count_falses;
    for (int j = 0; j < candidate_count; j++)
    {
        count_falses = 0;
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j] == false)
            {
                count_falses++;
            }
        }
        if (count_falses == candidate_count)
        {
            printf("%s\n", candidates[j]);
            break;
        }
    }
    return;
}
