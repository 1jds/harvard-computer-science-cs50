#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // prompt user for a positive integer between 1 and 8, inclusive
    int height = 0;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // build pyramid
    for (int i = 0; i < height; i++)
    {
        int left_side_hashes = i + 1;
        int left_side_spaces = height - left_side_hashes;
        while (left_side_spaces > 0)
        {
            printf(" ");
            left_side_spaces--;
        }
        while (left_side_hashes > 0)
        {
            printf("#");
            left_side_hashes--;
        }
        printf("\n");
    }
}
