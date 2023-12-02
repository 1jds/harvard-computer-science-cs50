import re


def main():
    # get card number from user
    user_input = get_string("Number: ")
    length_of_user_input = len(user_input)
    user_input_to_int_list = [int(i, 10) for i in user_input]

    # validate length
    is_valid_length = check_length(length_of_user_input)
    if not is_valid_length:
        print("INVALID")
        return

    # validate Luhn pattern
    is_valid_luhn_pattern = check_luhn_pattern(user_input_to_int_list)
    if not is_valid_luhn_pattern:
        print("INVALID")
        return

    # if both the length and Luhn pattern are valid, print the card company
    card_company(user_input, length_of_user_input, user_input_to_int_list)


def check_length(length):
    if length != 13 and length != 15 and length != 16:
        return False
    return True


def check_luhn_pattern(user_input_to_int_list):
    sum_of_second_digits = 0
    sum_of_other_digits = 0
    index = 1

    for i in reversed(user_input_to_int_list):
        if index % 2 == 0:
            list_of_digits = [int(i) for i in str(i * 2)]
            for j in list_of_digits:
                sum_of_second_digits += j
        else:
            sum_of_other_digits += i
        index += 1
    if (sum_of_second_digits + sum_of_other_digits) % 10 == 0:
        return True
    return False


def card_company(user_input, length_of_user_input, user_input_to_int_list):
    if not re.match(r"^34|37", user_input) == None:  # returns False if found
        print("AMEX")
    elif not re.match(r"^4", user_input) == None:
        print("VISA")
    elif not re.match(r"^51|52|53|54|55", user_input) == None:
        print("MASTERCARD")
    else:
        print("INVALID")


# Just going ahead and copying the CS50 library source code into here
# and change it a bit, because the import wasn't working.
def get_int(s):
    while True:
        if s is None:
            return None
        if re.search(r"^[+-]?\d+$", s):
            try:
                return int(s, 10)
            except ValueError:
                pass


def get_string(prompt):
    if not isinstance(prompt, str):
        raise TypeError("prompt must be of type str")
    try:
        return input(prompt)
    except EOFError:
        return None


main()
