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
void print_pref(void);
void print_pairs(void);
void mergeSort(pair array[], int arraylength);
void merge(pair leftArray[], pair rightArray[], pair array[], int leftSize, int rightSize);
bool checkCycle(int pairWinner, int pairLoser);
void print_locked(void);
bool noLose(int candidate);

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
bool vote(int rank, string name, int ranks[])
{
    // loop through the candidate array
    for (int i = 0; i < candidate_count; i++)
    {
        // if the vote matched any candidate in the array, if matched, i will be the matched
        // candidate index
        if (strcmp(candidates[i], name) == 0)
        {
            int matchedCandidateIndex = i;
            // and if the rank array is not empty
            // if ( rank_counter != 0)
            // {
            //     // if the rank array has anything, loop through the rank array until the current
            //     rank_counter for ( int j = 0; j < *rank_counter; j++)
            //     {
            //         // and check if the current matched candidate index is in the rank array
            //         // return false if it is in it
            //         if (matchedCandidateIndex == ranks[j])
            //         {
            //             return false;
            //         }
            //     }
            // }
            ranks[rank] = matchedCandidateIndex; // store the index of candidate in the candidate
                                                 // array to ranks
            // (*rank_counter)++; // increment the rank array counter as record inserted
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // iterate through the rank array, for the ith candidtate
    for (int i = 0; i < candidate_count; i++)
    {
        // Loop through the rank array for the jth candidate, start from i + 1, means start from the
        // rank that lower than i
        for (int j = i + 1; j < candidate_count; j++)
        {
            // update the preference
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // iterate through the candidate array, for the ith candidtate
    for (int i = 0; i < candidate_count; i++)
    {
        // Loop through the candidate array for the jth candidate, start from i + 1, to prevent
        for (int j = i + 1; j < candidate_count; j++)
        {
            // compare i j over j i and record it in the pair array
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
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Loop through the pair array first
    // and then loop through the preference array to check the preference power
    // sort them by the preferences
    mergeSort(pairs, pair_count);
    print_pairs();
    return;
}

void mergeSort(pair array[], int arraylength)
{
    if (arraylength <= 1)
        return; // base case

    // divide the array into two subarrays
    int middle = arraylength / 2;
    pair leftArray[middle];
    pair rightArray[arraylength - middle];

    int i = 0; // INdex for left array
    int j = 0; // index for right array

    // add the content of the array to left array and right array
    for (; i < arraylength; i++)
    {
        if (i < middle)
        {
            leftArray[i] = array[i];
        }
        else
        {
            rightArray[j] = array[i];
            j++;
        }
    }

    // recursive call of the merge sort of left array
    mergeSort(leftArray, middle);
    // recursive call of the merge sort of right array
    mergeSort(rightArray, arraylength - middle);
    // merge the array together
    merge(leftArray, rightArray, array, middle, arraylength - middle);
}

void merge(pair leftArray[], pair rightArray[], pair array[], int leftSize, int rightSize)
{
    // Indices of the arrays
    int i = 0, l = 0, r = 0;

    // looping through the left array and right array at the same time
    while (l < leftSize && r < rightSize)
    {
        // sorting the array by the margin in the preference array
        // the power of the left array is higher than that of the right
        if ((preferences[leftArray[l].winner][leftArray[l].loser] -
             preferences[leftArray[l].loser][leftArray[l].winner]) >
            (preferences[rightArray[r].winner][rightArray[r].loser] -
             preferences[rightArray[r].loser][rightArray[r].winner]))
        {
            // update the original array to the left's one
            array[i] = leftArray[l];
            i++;
            l++;
        }
        else
        {
            // update the original array to the right's one
            array[i] = rightArray[r];
            i++;
            r++;
        }
    }

    // handling the remaining item in the left array or right array
    while (l < leftSize)
    {
        array[i] = leftArray[l];
        i++;
        l++;
    }
    while (r < rightSize)
    {
        array[i] = rightArray[r];
        i++;
        r++;
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // if the pairs did not create cycle
    // loop through the pair array
    // add it in the loced array
    for (int i = 0; i < pair_count; i++)
    {
        if (!checkCycle(pairs[i].winner, pairs[i].loser)) // if no cycle found
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    print_locked();
    return;
}

// Function to check if there is cycle in the locked array, return true if a cycle found, return
// false if no cycle found.
bool checkCycle(int pairWinner, int pairLoser)
{
    // loop through the locked array, add to the locked array if there is no loop in the locked
    // array Example: a,b; b,c in the locked graph checkCycle(c,a)
    for (int i = 0; i < candidate_count; i++)
    {
        // if found any pair that the pairLoser has edge in the locked graph
        if (locked[pairLoser][i] == 1)
        { // Example: [a][b] is found
            // CHecking direct loop
            // if the pair Winner is i, it created a loop, return true
            if (pairWinner == i)
                return true; // i = b, not equal c, so return false
            // else further check down the cycle
            // as pairWinner wins pairLoser
            // checking if the pairWinner also win the loser of the pairLoser, i.e. i
            // if pairWinner cannot win the pairLoser > will return true
            int result = checkCycle(
                pairWinner,
                i); // pass down the loop by checkCycle(c, b); => in this case it will return true
            if (result == true)
                return true;
        }
    }
    // Return false if no cycle found
    return false;
}

// Print the winner of the election
void print_winner(void)
{

    // find the candidate that has not lose to any other candidate
    for (int i = 0; i < candidate_count; i++)
    {
        if (noLose(i))
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

bool noLose(int candidate)
{
    // loop throght the Locked Array, using candidate as loser
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][candidate])
        {
            return false;
        }
    }
    return true;
}

// Helper function to print the pref array out and check
void print_pref(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Loop through the rank array for the jth candidate, start from i + 1, means start from the
        // rank that lower than i
        for (int j = i + 1; j < candidate_count; j++)
        {
            printf("preferences of [%s] over [%s] is %d\n", candidates[i], candidates[j],
                   preferences[i][j]);
        }
    }
}

void print_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        printf("Pair %d: Winner = %d, Loser = %d, Power: %d \n", i, pairs[i].winner, pairs[i].loser,
               preferences[pairs[i].winner][pairs[i].loser]);
    }
}

void print_locked(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("Locked %d, %d is %d \n", i, j, locked[i][j]);
        }
    }
}
