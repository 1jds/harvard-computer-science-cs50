#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

void get_counts(string text, int *letters, int *words, int *sentences);
int get_grade(int l, int w, int s);

int main(void)
{
    int l = 0;
    int w = 1; // becuase there is no whitespace before first word
    int s = 0;

    string user_input = get_string("Text: ");

    get_counts(user_input, &l, &w, &s);

    int grade = get_grade(l, w, s);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    else
    {
        printf("Grade %i\n", grade);
        return 0;
    }

    return 1;
}

int get_grade(int l, int w, int s)
{
    float avg_letters_per_100_words = (float) l / (float) w * 100;
    float avg_sentences_per_100_words = (float) s / (float) w * 100;
    float index = (0.0588 * avg_letters_per_100_words) - (0.296 * avg_sentences_per_100_words) - 15.8;
    int result = (int) round(index);
    return result;
}

void get_counts(string text, int *letters, int *words, int *sentences)
{
    int text_length = strlen(text);
    for (int i = 0; i < text_length; i++)
    {
        if (isalpha(text[i]))
        {
            *letters = *letters + 1;
        }
        else if (text[i] == 32)
        {
            *words = *words + 1;
        }
        else if (text[i] == 33 || text[i] == 63 || text[i] == 46)
        {
            *sentences = *sentences + 1;
        }
    }
}
