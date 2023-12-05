# Works for Bob! But a lot of hard-coding I need to get rid of...

import csv
import sys
from typing import List, Dict

def main():

    # TODO: Check for command-line usage
    if not len(sys.argv) == 3 or not sys.argv[1][-4:] == ".csv" or not sys.argv[2][-4:] == ".txt":
        print("Usage: python dna.py data.csv sequence.txt")

# $ python dna.py databases/small.csv sequences/1.txt
# Lavender


    # TODO: Read database file into a variable
    list_from_csv_file: List[Dict[str, int]] = []  # Or, as we would say in JavaScript, 'array'! With some typing here...
    csv_file = open("databases/small.csv")
    my_csv_reader_dictionary = csv.DictReader(csv_file)

    for row in my_csv_reader_dictionary:
        int_row: Dict[str, float] = {}
        for column in row:
            if not column == 'name':
                int_row[column] = int(row[column])
            else:
                int_row[column] = row[column]
        list_from_csv_file.append(int_row)
    # print(list_from_csv_file)
    csv_file.close()

    # TODO: Read DNA sequence file into a variable
    individuals_sequence_file = open("sequences/1.txt", "r")
    sequence_string = individuals_sequence_file.readline()
    # print(sequence_string)
    individuals_sequence_file.close()

    # TODO: Find longest match of each STR in DNA sequence
    # STRs are as follows in the small file: AGATC, AATG, TATC
    longest_match_for_AGATC = longest_match(sequence_string, 'AGATC')
    longest_match_for_AATG = longest_match(sequence_string, 'AATG')
    longest_match_for_TATC = longest_match(sequence_string, 'TATC')
    # print(longest_match_for_AGATC)
    # print(longest_match_for_AATG)
    # print(longest_match_for_TATC)

    # TODO: Check database for matching profiles
    dna_owner = "No match"
    # iterate through this list_from_csv_file
    for dict in list_from_csv_file: # 'dict', or as we would say in JavaScript, 'object'!
        if dict['AGATC'] == longest_match_for_AGATC and dict['AATG'] == longest_match_for_AATG and dict['TATC'] == longest_match_for_TATC:
            dna_owner = dict['name']

    print(dna_owner)

    return


def longest_match(sequence, subsequence):
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
