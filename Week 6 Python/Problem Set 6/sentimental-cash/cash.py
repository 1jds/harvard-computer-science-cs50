import math
import re


def main():
    # Ask how many dollars the customer is owed in change
    while True:
        dollars = get_float("Change owed: ")
        if dollars > 0:
            break
        else:
            print("Enter a positive number")

    # Calculate the number of quarters to give the customer
    quarters = calculate_quarters(dollars)
    dollars = round(dollars - quarters * 0.25, 2)

    # Calculate the number of dimes to give the customer
    dimes = calculate_dimes(dollars)
    dollars = round(dollars - dimes * 0.10, 2)

    # Calculate the number of nickels to give the customer
    nickels = calculate_nickels(dollars)
    dollars = round(dollars - nickels * 0.05, 2)

    # Calculate the number of pennies to give the customer
    pennies = calculate_pennies(dollars)
    dollars = round(dollars - pennies * 0.01, 2)

    # Sum coins
    coins = quarters + dimes + nickels + pennies

    # Print total number of coins to give the customer
    print(coins)


def calculate_quarters(dollars):
    return math.trunc(dollars / 0.25)


def calculate_dimes(dollars):
    return math.trunc(dollars / 0.10)


def calculate_nickels(dollars):
    return math.trunc(dollars / 0.05)


def calculate_pennies(dollars):
    return math.trunc(dollars / 0.01)


# Just going ahead and copying the CS50 library source code into here, because the import wasn't working.
def get_float(prompt):
    """
    Read a line of text from standard input and return the equivalent float
    as precisely as possible; if text does not represent a double, user is
    prompted to retry. If line can't be read, return None.
    """
    while True:
        s = get_string(prompt)
        if s is None:
            return None
        if len(s) > 0 and re.search(r"^[+-]?\d*(?:\.\d*)?$", s):
            try:
                return float(s)
            except (OverflowError, ValueError):
                pass


def get_string(prompt):
    """
    Read a line of text from standard input and return it as a string,
    sans trailing line ending. Supports CR (\r), LF (\n), and CRLF (\r\n)
    as line endings. If user inputs only a line ending, returns "", not None.
    Returns None upon error or no input whatsoever (i.e., just EOF).
    """
    if not isinstance(prompt, str):
        raise TypeError("prompt must be of type str")
    try:
        return input(prompt)
    except EOFError:
        return None


main()
