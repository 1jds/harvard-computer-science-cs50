#include <cs50.h>
#include <stdio.h>
#include <string.h>

char *replace(char *str);
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./no-vowels <word-to-translate> \n");
        return 1;
    }
    char *result = replace(argv[1]);
    printf("%s\n", result);
    return 0;
}

char *replace(char *str)
{
    int str_length = strlen(str);
    for (int i = 0; i < str_length; i++)
    {
        switch (str[i])
        {
            case 'a':
                str[i] = '6';
                break;

            case 'e':
                str[i] = '3';
                break;

            case 'i':
                str[i] = '1';
                break;

            case 'o':
                str[i] = '0';
                break;
        }
    }
    return str;
}
