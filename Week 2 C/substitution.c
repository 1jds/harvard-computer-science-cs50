#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int check_argument_is_alphabetic(string argument1);
int check_argument_letters_not_doubled(string argument1);
void ciphered_text(string plaintext, string argument1);

const char alphabet[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                           'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\0'};
const char alphabet_capitals[27] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
                                    'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0'};

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

    if (strlen(argv[1]) != 26) // If user's command-line argument isn’t the right length
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    int is_argument_alphabetic =
        check_argument_is_alphabetic(argv[1]); // If user's argument contains anything except upper or lowercase letters
    if (is_argument_alphabetic == 1)
    {
        return 1;
    }

    int is_any_letter_doubled =
        check_argument_letters_not_doubled(argv[1]); // check that the CLI argument/cipher key contains each letter only once
    if (is_any_letter_doubled == 1)
    {
        return 1;
    }

    // prompt user for plaintext
    string plaintext = get_string("plaintext:  ");

    // display ciphered text
    printf("ciphertext: ");
    ciphered_text(plaintext, argv[1]); // pass plaintext to this function to cipher and print it
    printf("\n");

    return 0;
}

int check_argument_is_alphabetic(string argument1)
{
    int string_length = strlen(argument1);
    int numeric_value_of_character = 0;
    for (int i = 0; i < string_length; i++)
    {
        numeric_value_of_character = (int) argument1[i];
        if (numeric_value_of_character < 65 || numeric_value_of_character > 122)
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
    return 0;
}

int check_argument_letters_not_doubled(string argument1)
{
    char str1[27]; // copy the argument passed in just to avoid mutating the original
    for (int i = 0; i < 27; i++)
    {
        str1[i] = argument1[i];
    }

    char str1_lowercase[27]; // make lowercase so that the following sort will work
    for (int i = 0; i < 27; i++)
    {
        str1_lowercase[i] = tolower(str1[i]);
    }

    // sort array alphabetically
    int counter = 26; // We use 26 and not 27 for the counter, because sorting the '\0' in causes problems.
    for (int i = 0; i < counter; i++)
    {
        for (int j = i; j < counter; j++)
        {
            if (str1_lowercase[i] > str1_lowercase[j])
            {
                char tempchar;
                tempchar = str1_lowercase[i];
                str1_lowercase[i] = str1_lowercase[j];
                str1_lowercase[j] = tempchar;
            }
        }
    }

    if (strcmp(str1_lowercase, alphabet) != 0) // compare the user string to our alphabet constant
    {
        return 1;
    }
    return 0;
}

void ciphered_text(string plaintext, string argument1)
{
    int plaintext_length = strlen(plaintext);
    char plaintext_copy[plaintext_length];    // copy the plaintext passed in just to avoid mutating the original
    for (int i = 0; i < plaintext_length; i++)
    {
        plaintext_copy[i] = plaintext[i];
    }

    char cipher_lowercase[27];
    for (int i = 0; i < 27; i++)
    {
        cipher_lowercase[i] = tolower(argument1[i]);
    }

    char cipher_capitals[27];
    for (int i = 0; i < 27; i++)
    {
        cipher_capitals[i] = toupper(argument1[i]);
    }

    for (int i = 0; i < plaintext_length; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (plaintext[i] == alphabet[j])
            {
                plaintext_copy[i] = cipher_lowercase[j];
            }
            else if (plaintext[i] == alphabet_capitals[j])
            {
                plaintext_copy[i] = cipher_capitals[j];
            }
        }
    }

    for (int i = 0; i < plaintext_length; i++)
    {
        printf("%c", plaintext_copy[i]);
    }
}
