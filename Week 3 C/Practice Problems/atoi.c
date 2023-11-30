#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input, int length, int temp_length);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    int n = strlen(input);

    for (int i = 0; i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input, n, n));
}

int convert(string input, int length, int temp_length)
{
    char curr_char = input[temp_length - 1];
    int curr_int = 0;

    switch (curr_char)
    {
        case '1':
            curr_int = 1;
            break;
        case '2':
            curr_int = 2;
            break;
        case '3':
            curr_int = 3;
            break;
        case '4':
            curr_int = 4;
            break;
        case '5':
            curr_int = 5;
            break;
        case '6':
            curr_int = 6;
            break;
        case '7':
            curr_int = 7;
            break;
        case '8':
            curr_int = 8;
            break;
        case '9':
            curr_int = 9;
            break;
        default:
            curr_int = 0;
    }

    int multiplier_factor = 1;
    int difference_in_lengths = length - temp_length;
    for (int i = difference_in_lengths; i > 0; i--)
    {
        multiplier_factor *= 10;
    }
    if (temp_length == 0)
    {
        return 0;
    }
    return curr_int * multiplier_factor + convert(input, length, temp_length - 1);
}
