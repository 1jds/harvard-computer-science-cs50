import csv
from cs50 import SQL
from os import path, system


def main(FILENAME="students.csv", DB_NAME="hogwarts.db", SCHEMA="schema.sql"):
    # Create list of dictionaries containing student into data
    student_data = []

    # Open CSV file
    try:
        with open(FILENAME, "r") as student_info_file:
            # Create DictReader
            student_info_reader = csv.DictReader(student_info_file)

            # Iterate over CSV file, to insert info into database
            for row in student_info_reader:
                student_data.append(row)
    except:
        print("An error has occured while opening the file")
        return 1

    # Open database
    if path.exists(DB_NAME):
        db = SQL(f"sqlite:///{DB_NAME}")
    else:
        print("Database not found")
        return 1

    # Create Tables according to Schema
    system(f"sqlite3 {DB_NAME} < {SCHEMA}")

    # Insert student data into database
    for student in student_data:
        # Insert student names into students table
        db.execute(
            "INSERT OR IGNORE INTO students (student_id, student_name) VALUES (?, ?)",
            student["id"],
            student["student_name"],
        )
        # Insert house data into houses table
        db.execute(
            "INSERT OR IGNORE INTO houses (house_name, house_head_name) VALUES (?, ?)",
            student["house"],
            student["head"],
        )
        # Insert ids into studentshouses junction table
        db.execute(
            "INSERT OR IGNORE INTO studentshouses (student_id, house_id) VALUES (?, ?)",
            student["id"],
            student["house"],
        )

    print("Insertion of data into database complete")
    return 0


if __name__ == "__main__":
    main()
