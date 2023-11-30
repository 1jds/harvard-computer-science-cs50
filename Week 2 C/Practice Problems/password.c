// Check that a password has at least one lowercase letter, uppercase letter, number and symbol

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

bool valid(string password)
{
    bool is_valid_password = false;
    bool has_lowercase = false;
    bool has_uppercase = false;
    bool has_number = false;
    bool has_symbol = false;

    int string_length = strlen(password);
    for (int i = 0; i < string_length; i++)
    {

        if (islower(password[i]))
        {
            has_lowercase = true;
        }
        if (isupper(password[i]))
        {
            has_uppercase = true;
        }
        if (isdigit(password[i]))
        {
            has_number = true;
        }
        if (!isalnum(password[i]))
        {
            has_symbol = true;
        }
    }

    if (has_lowercase && has_uppercase && has_number && has_symbol)
    {
        is_valid_password = true;
    }

    return is_valid_password;
}
