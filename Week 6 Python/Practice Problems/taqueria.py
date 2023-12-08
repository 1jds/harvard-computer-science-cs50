menu = {
    "Baja Taco": 4.25,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00,
}


def main():
    running_total = 0.00

    while True:
        try:
            item = input("Item: ").title()
            if item in menu:
                running_total += menu[item]
            print("Total: ${:0.2f}".format(running_total))
        except EOFError:
            print("\n")
            break


main()
