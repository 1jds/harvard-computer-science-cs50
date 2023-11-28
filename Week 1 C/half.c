// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value

#include <cs50.h>
#include <stdio.h>

float half(float bill, float tax, int tip);

int main(void)
{
    float bill_amount = get_float("Bill before tax and tip: ");
    float tax_percent = get_float("Sale Tax Percent: ");
    int tip_percent = get_int("Tip percent: ");

    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

// TODO: Complete the function
float half(float bill, float tax, int tip)
{
    float after_tax = bill + (tax / 100 * bill);
    float after_tip = after_tax + ((float) tip / 100 * after_tax);
    // printf("The total plus tax is... %f. Adding a tip to that total gives... %f\n", after_tax, after_tip);
    float total_halved = after_tip / 2;
    return total_halved;
}
