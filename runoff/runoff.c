#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define PRINT_2D_ARRAY(arr, rows, cols)                                                            \
    do                                                                                             \
    {                                                                                              \
        for (int i = 0; i < (rows); i++)                                                           \
        {                                                                                          \
            for (int j = 0; j < (cols); j++)                                                       \
                printf("%d ", (arr)[i][j]);                                                        \
            printf("\n");                                                                          \
        }                                                                                          \
    }                                                                                              \
    while (0)

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int candidate_index = 0; candidate_index < candidate_count; candidate_index++)
    {
        if (strcmp(name, candidates[candidate_index].name) == 0)
        {
            preferences[voter][rank] = candidate_index;
            return true;
        }
    }

    // TODO
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].votes = 0;
    }
    for (int voter_index = 0; voter_index < voter_count; voter_index++)
    {
        for (int rank_index = 0; rank_index < candidate_count; rank_index++)
        {

            if (!candidates[preferences[voter_index][rank_index]].eliminated)
            {
                candidates[preferences[voter_index][rank_index]].votes++;
                break;
            }
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int majority_votes = voter_count / 2 + 1;
    for (int candidate_index = 0; candidate_index < candidate_count; candidate_index++)
    {
        if (candidates[candidate_index].votes >= majority_votes)
        {
            printf("%s\n", candidates[candidate_index].name);
            return true;
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = voter_count;
    for (int candidate_index = 0; candidate_index < candidate_count; candidate_index++)
    {
        if (candidates[candidate_index].votes < min && (!candidates[candidate_index].eliminated))
        {
            min = candidates[candidate_index].votes;
        }
    }
    // TODO
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int candidate_index = 0; candidate_index < candidate_count; candidate_index++)
    {
        if (min != candidates[candidate_index].votes && (!candidates[candidate_index].eliminated))
        {
            return false;
        }
    }
    // TODO
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int candidate_index = 0; candidate_index < candidate_count; candidate_index++)
    {
        if (min == candidates[candidate_index].votes && (!candidates[candidate_index].eliminated))
        {
            candidates[candidate_index].eliminated = true;
        }
    }
}
