#include <cs50.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

bool check_length(int card_length_count);
bool check_luhn_pattern(long card_number, int card_length_count);
int sum_digits_in_arr(int counter, int arr[]);
string card_company(long card_number, int card_length_count);

int main(void)
{
    // get card number from user
    long card_number = get_long("Number: ");

    // get length of card number in digits
    int card_length_count = 0;
    long n = card_number;
    while (n != 0)
    {
        n = n / 10;
        card_length_count++;
    }

    // validate length
    bool is_valid_length = check_length(card_length_count);
    // validate Luhn pattern
    bool is_valid_luhn_pattern;
    if (is_valid_length)
    {
        is_valid_luhn_pattern = check_luhn_pattern(card_number, card_length_count);
    }
    // if both the length and Luhn pattern are valid, check the card number for company
    if (is_valid_length && is_valid_luhn_pattern)
    {
        string company_name = card_company(card_number, card_length_count);
        printf("%s", company_name);
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}

bool check_length(int card_length_count)
{
    if (card_length_count != 13 && card_length_count != 15 && card_length_count != 16)
    {
        return false;
    }
    return true;
}

bool check_luhn_pattern(long card_number, int card_length_count)
{
    // determine whether the odd or even digits in the card number will be doubled
    int odds_multiplier;
    int evens_multiplier;
    if (card_length_count % 2 == 0)
    {
        odds_multiplier = 2;
        evens_multiplier = 1;
    }
    else
    {
        odds_multiplier = 1;
        evens_multiplier = 2;
    }

    // determine length of each sub-array from total length of card digits
    int length_of_evens_arr;
    int length_of_odds_arr;
    if (card_length_count % 2 == 0)
    {
        length_of_evens_arr = card_length_count / 2;
        length_of_odds_arr = card_length_count / 2;
    }
    else
    {
        length_of_evens_arr = card_length_count / 2;
        length_of_odds_arr = card_length_count / 2 + 1;
    }

    // Initialise the three arrays we'll be working with
    int array_of_card_digits[card_length_count];
    int evens_array[length_of_evens_arr];
    int odds_array[length_of_odds_arr];

    // populate array of digits from card number entered by user
    for (int i = card_length_count; i > 0; i--)
    {
        array_of_card_digits[card_length_count - i] = (long) (card_number / pow(10, i - 1)) % 10;
        // printf("%d : %i\n", card_length_count - i, array_of_card_digits[card_length_count - i]);
    }

    // populate sub-arrays of odds and evens with digits from card digits array
    int j = 0;
    int k = 0;
    for (int i = 0; i < card_length_count; i++)
    {
        // the conditional here might seem to be finding evens rather than odds,
        // but because arrays are zero-indexed, it's finding odd items
        if (i % 2 == 0)
        {
            odds_array[j] = (int) array_of_card_digits[i] * odds_multiplier;
            j++;
        }
        else
        {
            evens_array[k] = (int) array_of_card_digits[i] * evens_multiplier;
            k++;
        }
    }

    // determine the sum of all digits in the two sub-arrays and then make a total
    int sum_of_evens_arr = sum_digits_in_arr(length_of_evens_arr, evens_array);
    int sum_of_odds_arr = sum_digits_in_arr(length_of_odds_arr, odds_array);
    int total = sum_of_evens_arr + sum_of_odds_arr;

    // determine whether the modulo 10 of the total is congruent to 0
    bool result;
    if (total % 10 == 0)
    {
        result = true;
    }
    else
    {
        result = false;
    }

    return result;
}

int sum_digits_in_arr(int counter, int arr[])
{
    int sum = 0;
    for (int i = 0; i < counter; i++)
    {
        int n = arr[i];
        int a;
        a = n % 10; // last digit stripped off
        n = n / 10; // remaining digit (or 0 if none)
        sum = sum + a + n;
    }
    return sum;
}

string card_company(long card_number, int card_length_count)
{
    if (card_length_count == 15)
    {
        int first_two_digits = card_number / 10000000000000;
        if (first_two_digits == 34 || first_two_digits == 37)
        {
            return "AMEX\n";
        }
    }
    else if (card_length_count == 16)
    {
        int first_digit = card_number / 1000000000000000;
        if (first_digit == 4)
        {
            return "VISA\n";
        }
        else if (first_digit == 5)
        {
            int first_two_digits = card_number / 100000000000000;
            if (first_two_digits > 50 && first_two_digits < 56)
            {
                return "MASTERCARD\n";
            }
        }
    }
    else if (card_length_count == 13)
    {
        int first_digit = card_number / 1000000000000;
        if (first_digit == 4)
        {
            return "VISA\n";
        }
    }
    return "INVALID\n";
}

// NOTES:
// American Express cards are 15 digits long
// MasterCard cards are 16 digits long
// Visa cards are either 13 or 16 digits long

// American Express cards start with 34 or 37
// MasterCard cards start with 51, 52, 53, 54, or 55
// Visa cards start with 4
