def main():
    while True:
        try:
            height = int(input("Height: "))
            if height > 0 and height < 9:
                break
            else:
                print("Enter a number between 1 and 8")
        except:
            print("Enter a number between 1 and 8")

    i = 1
    while i <= height:
        print_spaces(height - i)
        print_hashes(i)
        i = i + 1


def print_spaces(n):
    for i in range(n):
        print(" ", end="")


def print_hashes(n):
    for i in range(n):
        print("#", end="")
    print()


main()
