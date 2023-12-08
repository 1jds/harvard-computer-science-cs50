from pyfiglet import Figlet
import random
import sys

figlet = Figlet()


def main():
    # List of figlet fonts
    fonts_list = figlet.getFonts()

    # Does the user want a random font
    choose_random_font = False

    # Ensure correct usage
    length_of_args = len(sys.argv)
    if length_of_args == 1:  # For a random font
        choose_random_font = True
    elif length_of_args == 3:  # For a specified font
        print(sys.argv[1])
        if not sys.argv[1] == "-f" or sys.argv[1] == "--font":
            sys.exit("Invalid usage")
        user_chosen_font = sys.argv[2]
        if user_chosen_font in fonts_list:
            figlet.setFont(font=user_chosen_font)
        else:
            sys.exit("Invalid usage")
    else:  # For incorrect number of command line arguments
        sys.exit("Invalid usage")

    if choose_random_font:
        random_font = random.choice(fonts_list)
        figlet.setFont(font=random_font)

    user_text = input("Input: ")
    print("Output:")
    print(figlet.renderText(user_text))


main()
