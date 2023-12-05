import csv
import sys
from typing import List, Dict


def main():
    # Check for command-line usage
    if (
        not len(sys.argv) == 3
        or not sys.argv[1][-4:] == ".csv"
        or not sys.argv[2][-4:] == ".txt"
    ):
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Read database .csv file into a list of dicts / array of objects
    list_from_csv_file: List[
        Dict[str, int]
    ] = []  # honestly, just using types here to experiment a bit
    csv_file = open(sys.argv[1], "r", encoding="utf8")
    my_csv_reader_dictionary = csv.DictReader(csv_file)
    for row in my_csv_reader_dictionary:
        int_row: Dict[str, float] = {}
        for column in row:
            if not column == "name":
                int_row[column] = int(row[column])
            else:
                int_row[column] = row[column]
        list_from_csv_file.append(int_row)
    list_of_column_names = my_csv_reader_dictionary.fieldnames
    csv_file.close()

    # Read DNA sequence file into a variable
    individuals_sequence_file = open(sys.argv[2], "r", encoding="utf8")
    sequence_string = individuals_sequence_file.readline()
    individuals_sequence_file.close()

    # Find longest match of each STR in DNA sequence
    list_of_longest_matches = []
    for i in range(1, len(list_of_column_names)):
        list_of_longest_matches.append(
            longest_match(sequence_string, list_of_column_names[i])
        )

    # Check database for matching profiles
    dna_owner = "No match"
    for dict in list_from_csv_file:
        match = True
        for key in range(0, len(list_of_longest_matches)):
            if not dict[list_of_column_names[key + 1]] == list_of_longest_matches[key]:
                match = False
        if match:
            dna_owner = dict["name"]
    print(dna_owner)

    return


def longest_match(
    sequence, subsequence
):  # This function was made by the CS50 staff. The main function above was implemented by me
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
