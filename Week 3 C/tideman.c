#include <cs50.h>
#include <stdio.h>
#include <strings.h>

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
} pair;

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
bool middle_cycle_exists(int winner, int loser);
bool final_cycle_exists(int loser);

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

    // int preferences[i][j];
    printf("The current state of the preferences 2d array:\n");
    for (int x = 0; x < candidate_count; x++)
    {
        printf("For %s:\n", candidates[x]);
        for (int y = 0; y < candidate_count; y++)
        {
            printf("%i people prefer %s over %s\n", preferences[x][y], candidates[x], candidates[y]);
        }
        printf("\n");
    }

    add_pairs();

    for (int q = 0; q < pair_count; q++)
    {
        printf("For pair %i\n", q);
        printf("Winner = %i\n", pairs[q].winner);
        printf("Loser = %i\n", pairs[q].loser);
        printf("\n");
    }

    sort_pairs();

    for (int k = 0; k < pair_count; k++)
    {
        printf("The number of votes for candidate %i over %i was %i\n", pairs[k].winner, pairs[k].loser,
               preferences[pairs[k].winner][pairs[k].loser]);
    }

    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
// of course this won't check that a voter has entered
// the same name twice for two different preference ranks...
{
    bool is_valid_candidate_name = false;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcasecmp(candidates[i], name) == 0)
        {
            is_valid_candidate_name = true;
            ranks[rank] = i;
        }
    }
    return is_valid_candidate_name;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j && !(j < i))
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count++;
                }
                else if (preferences[j][i] > preferences[i][j])
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair temp_pair;
    bool is_continue = true;
    do
    {
        int swaps_made = 0;
        for (int i = pair_count - 1; i > 0; i--)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] > preferences[pairs[i - 1].winner][pairs[i - 1].loser])
            {
                temp_pair = pairs[i];
                pairs[i] = pairs[i - 1];
                pairs[i - 1] = temp_pair;
                swaps_made++;
            }
        }
        if (swaps_made == 0)
        {
            is_continue = false;
        }
    }
    while (is_continue);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        if (!middle_cycle_exists(winner, loser) && !final_cycle_exists(loser))
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
        bool is_winner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                is_winner = false;
            }
        }
        if (is_winner)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

// check if middle cycle exists
bool middle_cycle_exists(int winner, int loser)
{
    bool is_cycle_exists = false;
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] == true)
        {
            // is loser's lock over current winner?
            if (i == winner)
            {
                is_cycle_exists = true;
            }
            else // if not, go to who it is over and check the same thing there...
            {
                is_cycle_exists = middle_cycle_exists(winner, i);
            }
        }
    }
    return is_cycle_exists;
}

// I really should be able to combine 'middle_cycle_exists' and 'final_cycle_exists' but this has already taken too long.
// So, optimising this is for another day!
// check if a cycle exists on final pair
bool final_cycle_exists(int loser)
{
    bool is_cycle_exists = false;
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] == true)
        {
            for (int j = 0; j < candidate_count; j++)
            {
                for (int k = 0; k < candidate_count; k++)
                {
                    if (locked[j][k] == true)
                    {
                        if (i == j)
                        {
                            is_cycle_exists = true;
                        }
                        else
                        {
                            is_cycle_exists = final_cycle_exists(i);
                        }
                    }
                }
            }
        }
    }
    return is_cycle_exists;
}
