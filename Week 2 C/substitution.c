#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

int check_argument_is_alphabetic(string argument1);
int check_argument_letters_not_doubled(string argument1);
char alphabet[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\0'};
char key_sequence[27];

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

    int is_argument_alphabetic = check_argument_is_alphabetic(argv[1]); // If user's argument contains anything except upper or lowercase letters
    if (is_argument_alphabetic == 1)
    {
        return 1;
    }

    int is_any_letter_doubled = check_argument_letters_not_doubled(argv[1]); // check that the command-line argument/cipher key contains each letter only once


    // prompt user for plaintext
    string plaintext = get_string("plaintext:  ");

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
   	// char arr[27] = {'z', 'a', 'c', 'd', 'k', 'm', 'n', 'h', 'i', 'j', 'g', 'l', 'f', 'e', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'b', '\0'};;

    char str1[27];
    for (int i = 0; i < 27; i++)
    {
        str1[i] = argument1[i];
        printf("%c", str1[i]);
    }

    printf("\n");

    // sort array alphabetically
	int counter = 27;
	for (int i = 0; i < counter; i++)
	{
		for (int j = i; j < counter; j++)
		{
			if (str1[i] > str1[j])
			{
				char tempchar;
				tempchar = str1[i];
				str1[i] = str1[j];
				str1[j] = tempchar;
			}
		}
	}

    for (int i = 0; i < 27; i++)
    {
        printf("%c", str1[i]);
    }
    printf("\n");
    for (int i = 0; i < 27; i++)
    {
        printf("%c", alphabet[i]);
    }
    printf("\n");

    int blah = strcasecmp(str1, alphabet);
    printf("%i\n", blah);

    if (strcasecmp(str1, alphabet) == -97)
    {
        printf("ZZZ... Those are the same.\n");
    }
    else
    {
        printf("ZZZ... Those are different.\n");
    }

    return 0;
}

    // char argument1_lowercased[string_length + 1];
    // for (int i = 0; i < string_length; i++)
    // {
    //     int tolower(char c);
    // }



// take input argument and convert it all to lowercase...
// sort array alphabetically (either by using characters or their numeric value)
// then compare that sorted array to the default alphabet array, such that one can determine if each character appears only once








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

