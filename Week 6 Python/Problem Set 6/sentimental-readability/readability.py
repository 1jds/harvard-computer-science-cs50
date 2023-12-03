from cs50 import get_string
import re


def main():
    # Get a string from the user to evaluate
    string = get_string("Text: ")

    # Calculate the number of characters, words, and sentences
    all_letters = re.findall(r"[a-zA-Z]", string)
    all_words = string.split()
    all_sentence_enders = re.findall(r"[.!?]", string)
    l = len(all_letters)
    w = len(all_words)
    s = len(all_sentence_enders)

    # Determine and display the reading grade level of the provided string
    grade_level = get_grade(l, w, s)
    if grade_level < 1:
        print("Before Grade 1")
    elif grade_level >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade_level}")


def get_grade(l, w, s):
    avg_letters_per_100_words = l / w * 100
    avg_sentences_per_100_words = s / w * 100
    index = (
        (0.0588 * avg_letters_per_100_words)
        - (0.296 * avg_sentences_per_100_words)
        - 15.8
    )
    result = round(index)
    return result


main()
