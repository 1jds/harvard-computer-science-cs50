#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    int winner = 1;
    if (score1 == score2)
    {
        printf("Tie!\n");
        return 0;
    }
    else if (score2 > score1)
    {
        winner = 2;
    }
    printf("Player %i wins!\n", winner);
    return 0;
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int score_counter = 0;
    int string_length = strlen(word);
    int numeric_value_of_string = 0;
    for (int i = 0; i < string_length; i++)
    {
        numeric_value_of_string = (int) word[i];
        if (numeric_value_of_string > 96 && numeric_value_of_string < 123)
        {
            score_counter = score_counter + POINTS[numeric_value_of_string - 97];
        }
        else if (numeric_value_of_string > 64 && numeric_value_of_string < 91)
        {
            score_counter = score_counter + POINTS[numeric_value_of_string - 65];
        }
    }
    return score_counter;
}
