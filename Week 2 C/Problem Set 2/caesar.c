#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_argument_is_numeric(string argument1);
void print_ciper_text(string plain_text, int key_value);

int main(int argc, string argv[])
{
    if (argc == 1) // If user provides no command-line argument print usage guide
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    if (argc > 2) // If user provides too many command-line arguments
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int check = check_argument_is_numeric(argv[1]); // If user's command-line argument isn’t a number
    if (check == 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string plain_text = get_string("plaintext:  ");
    int key_value = atoi(argv[1]);
    printf("ciphertext: ");
    print_ciper_text(plain_text, key_value);
    printf("\n");
    return 0;
}

void print_ciper_text(string plain_text, int key_value)
{
    int string_length = strlen(plain_text);
    int numeric_value_of_character = 0;
    for (int i = 0; i < string_length; i++)
    {
        numeric_value_of_character = (int) plain_text[i];
        if (numeric_value_of_character > 96 && numeric_value_of_character < 123) // lowercase characters
        {
            int result = (numeric_value_of_character - 97 + key_value) % 26;
            printf("%c", result + 97);
        }
        else if (numeric_value_of_character > 64 && numeric_value_of_character < 91) // uppercase characters
        {
            int result = (numeric_value_of_character - 65 + key_value) % 26;
            printf("%c", result + 65);
        }
        else // all other characters
        {
            printf("%c", numeric_value_of_character);
        }
    }
}

int check_argument_is_numeric(string argument1)
{
    int string_length = strlen(argument1);
    int numeric_value_of_character = 0;
    for (int i = 0; i < string_length; i++) // Loop to check each character is numeric
    {
        numeric_value_of_character = (int) argument1[i];
        if (numeric_value_of_character < 48 || numeric_value_of_character > 57)
        {
            return 1;
        }
    }
    return 0;
}
