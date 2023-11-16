#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int check_argument_is_valid(string argument1);
char key_sequence[26];

int main(int argc, string argv[])
{
    if (argc == 1) // If user provides no command-line argument print usage guide
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (argc > 2) // If user provides too many command-line arguments
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    int check = check_argument_is_valid(argv[1]); // If user's command-line argument isn’t the right length
    if (check == 1)
    {
        return 1;
    }

    // not containing each letter exactly once

    return 0;
}




int check_argument_is_valid(string argument1)
{
    int string_length = strlen(argument1);
    if (string_length != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    int numeric_value_of_character = 0;
    for (int i = 0; i < string_length; i++) // Loop to check each character is alphabetic
    {
        numeric_value_of_character = (int) argument1[i];
        if (numeric_value_of_character < 65 || numeric_value_of_character > 122) // 65-90 or 97-122
        {
            printf("Key must contain only alphabetic characters.\n");
            return 1;
        }
        else if (numeric_value_of_character > 90 && numeric_value_of_character < 97)
        {
            printf("Key must contain only alphabetic characters.\n");
            return 1;
        }
    }
    // char argument1_lowercased[string_length + 1];
    // for (int i = 0; i < string_length; i++)
    // {
    //     int tolower(char c);
    // }
    return 0;
}












// #include <cs50.h>
// #include <stdio.h>
// #include <stdlib.h>

// int check_argument_is_numeric(string argument1);
// void print_ciper_text(string plain_text, int key_value);

// int main(int argc, string argv[])
// {




//     string plain_text = get_string("plaintext:  ");
//     int key_value = atoi(argv[1]);
//     printf("ciphertext: ");
//     print_ciper_text(plain_text, key_value);
//     printf("\n");
//     return 0;
// }

// void print_ciper_text(string plain_text, int key_value)
// {
//     int string_length = strlen(plain_text);
//     int numeric_value_of_character = 0;
//     for (int i = 0; i < string_length; i++)
//     {
//         numeric_value_of_character = (int) plain_text[i];
//         if (numeric_value_of_character > 96 && numeric_value_of_character < 123) // lowercase characters
//         {
//             int result = (numeric_value_of_character - 97 + key_value) % 26;
//             printf("%c", result + 97);
//         }
//         else if (numeric_value_of_character > 64 && numeric_value_of_character < 91) // uppercase characters
//         {
//             int result = (numeric_value_of_character - 65 + key_value) % 26;
//             printf("%c", result + 65);
//         }
//         else // all other characters
//         {
//             printf("%c", numeric_value_of_character);
//         }
//     }
// }

