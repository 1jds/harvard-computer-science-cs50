import csv
import math
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each state
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    reader_data = []
    for row in reader:
        reader_data.append(row)

    previous_days_total = {}
    new_cases = {}

    # Populate the new_cases array with all state names and empty arrays
    for item in reader_data:
        if not item["state"] in new_cases:
            new_cases[item["state"]] = []

    # Populate the new_cases array for each state with last 14 days worth of data
    for row in reader_data:
        current_state = row["state"]
        current_cases = int(row["cases"])
        length_of_arr = len(new_cases[current_state])

        if length_of_arr == 0:
            new_cases[current_state].append(current_cases)
            previous_days_total[current_state] = current_cases
        else:
            new_cases[current_state].append(
                current_cases - previous_days_total[current_state]
            )
            previous_days_total[current_state] = current_cases
            if length_of_arr == 14:
                new_cases[current_state].pop(0)
    return new_cases


# Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for key, value in new_cases.items():
        if key in states:
            change = True
            difference = 0
            percent_change = 0
            increase_or_decrease = "an increase"
            first_week_avg = sum(value[0:7]) / 7
            second_week_avg = sum(value[7:]) / 7

            if first_week_avg > second_week_avg:
                increase_or_decrease = "a decrease"
                difference = first_week_avg - second_week_avg
            else:
                difference = second_week_avg - first_week_avg

            try:
                percent_change = difference / first_week_avg * 100
            except ZeroDivisionError:
                change = False

            if change:
                print(
                    f"{key} had a 7-day average of {math.trunc(second_week_avg)} and {increase_or_decrease} of {round(percent_change, 2)}%."
                )
            else:
                print(
                    f"No valid change in the 7-day average for {key} could be calculated."
                )


main()
