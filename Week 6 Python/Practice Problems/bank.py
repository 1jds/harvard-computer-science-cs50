import cs50

def main():
    user_input = cs50.get_string("Greeting: ")
    stripped_user_input = user_input.strip().lower()
    if stripped_user_input[0:5] == "hello":
        print("$0")
    elif stripped_user_input[0] == "h":
        print("$20")
    else:
        print("$100")


main()
