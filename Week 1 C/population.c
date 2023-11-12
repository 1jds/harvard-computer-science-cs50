#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start_size;
    do
    {
        start_size = get_int("Start size: ");
    }
    while (start_size < 9);

    // TODO: Prompt for end size
    int end_size;
    do
    {
        end_size = get_int("End size: ");
    }
    while (end_size < start_size);

    // TODO: Calculate number of years until we reach threshold
    int number_of_years_to_goal = 0;
    int running_total = start_size;

    while (running_total < end_size)
    {
        int new_births = running_total / 3;
        int new_deaths = running_total / 4;
        running_total = running_total + new_births - new_deaths;
        number_of_years_to_goal++;
    }

    // TODO: Print number of years
    printf("Years: %i\n", number_of_years_to_goal);
}
