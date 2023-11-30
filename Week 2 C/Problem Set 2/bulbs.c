#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // Get input word to convert
    string message = get_string("Message to encode: ");
    int string_length = strlen(message);

    // Loop over string
    int numeric_value_of_character = 0;
    for (int i = 0; i < string_length; i++)
    {
        // Turn each character in string into a decimal number in turn
        numeric_value_of_character = (int) message[i];
        // Turn decimal number into array of binary values
        int arr[BITS_IN_BYTE] = {0, 0, 0, 0, 0, 0, 0, 0};
        for (int j = 7; j > 0; j--)
        {
            if (numeric_value_of_character % 2 != 0)
            {
                arr[j] = 1;
            }
            numeric_value_of_character = numeric_value_of_character / 2;
        }
        for (int k = 0; k < 8; k++)
        {
            if (arr[k] == 0)
            {
                // add a 0 to output
                print_bulb(0);
            }
            else
            {
                // add a 1 to output
                print_bulb(1);
            }
        }
        printf("\n");
    }
    return 0;
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
