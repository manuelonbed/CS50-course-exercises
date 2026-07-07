#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer (candidate)i over (candidate)j
// preferences[i][j] is for the head to head
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
// update this array to true if head to head winner, else false
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

void print_pairs(pair arr[], int size);

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
bool check_cycle(int starting_candidate, int current_candidate);

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
    // This makes sure that the locked array starts with every element at false
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    //  Store number of voters INPUT from user
    int voter_count = get_int("Number of voters: ");

    // Query for votes (loops for number of voters)
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];
        for (int r = 0; r < candidate_count; r++)
        {
            ranks[r] = -1;
        }

        // Query for each voter rank (loops for number of candidates)
        for (int j = 0; j < candidate_count; j++)
        {
            // ask user to rank each candidate,
            // Rank j+1 = Rank 0+1

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
bool vote(int rank, string name, int ranks[])
{

    for (int l = 0; l < candidate_count; l++)
    {
        if (strcmp(name, candidates[l]) == 0)
        {
            /*if (ranks[l] != -1)
            {
                return false;
            }*/
            ranks[rank] = l;
            return true;
        }
    }

    // TODO
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

    for (int i = 0; i < candidate_count; i++)
    {
        int preference = ranks[i];
        for (int j = i + 1; j < candidate_count; j++)
        {
            int no_preference = ranks[j];
            preferences[preference][no_preference] += 1;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {

        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count = pair_count + 1;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count = pair_count + 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (i != j)
            {
                if (preferences[pairs[i].winner][pairs[i].loser] >
                    preferences[pairs[j].winner][pairs[j].loser])
                {
                    // swap the pairs
                    pair temp = pairs[i];
                    pairs[i] = pairs[j];
                    pairs[j] = temp;
                }
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        if (!check_cycle(winner, loser))
        {
            locked[winner][loser] = true;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool edge = false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                edge = true;
                break;
            }
        }
        if (!edge)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}

bool check_cycle(int starting_candidate, int current_candidate)
{
    if (starting_candidate == current_candidate)
    {
        return true;
    }
    for (int i = 0; i < pair_count; i++)
    {
        if (locked[current_candidate][i])
        {

            if (check_cycle(starting_candidate, i))
            {
                return true;
            }
        }
    }
    return false;
}
