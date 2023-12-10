-- This was the original schema:
-- sqlite> .schema
-- CREATE TABLE students (
--     id INTEGER,
--     student_name TEXT,
--     house TEXT,
--     head TEXT,
--     PRIMARY KEY(id)
-- );

-- Which produced the following results:
-- sqlite> SELECT * FROM students;
-- +----+------------------------+------------+--------------------+
-- | id |      student_name      |   house    |        head        |
-- +----+------------------------+------------+--------------------+
-- | 1  | Adelaide Murton        | Slytherin  | Severus Snape      |
-- | 2  | Adrian Pucey           | Slytherin  | Severus Snape      |
-- | 3  | Anthony Goldstein      | Ravenclaw  | Filius Flitwick    |
-- | 4  | Blaise Zabini          | Slytherin  | Severus Snape      |
-- | 5  | Cedric Diggory         | Hufflepuff | Pomona Sprout      |
-- | 6  | Cho Chang              | Ravenclaw  | Filius Flitwick    |
-- | 7  | Colin Creevey          | Gryffindor | Minerva McGonagall |
-- | 8  | Dean Thomas            | Gryffindor | Minerva McGonagall |
-- | 9  | Draco Lucius Malfoy    | Slytherin  | Severus Snape      |
-- | 10 | Ernest Macmillan       | Hufflepuff | Pomona Sprout      |
-- | 11 | Ginevra Molly Weasley  | Gryffindor | Minerva McGonagall |
-- | 12 | Gregory Goyle          | Slytherin  | Severus Snape      |
-- | 13 | Hannah Abbott          | Hufflepuff | Pomona Sprout      |
-- | 14 | Harry James Potter     | Gryffindor | Minerva McGonagall |
-- | 15 | Hermione Jean Granger  | Gryffindor | Minerva McGonagall |
-- | 16 | Isobel MacDougal       | Ravenclaw  | Filius Flitwick    |
-- | 17 | Justin Finch-Fletchley | Hufflepuff | Pomona Sprout      |
-- | 18 | Lavender Brown         | Gryffindor | Minerva McGonagall |
-- | 19 | Lisa Turpin            | Ravenclaw  | Filius Flitwick    |
-- | 20 | Luna Lovegood          | Ravenclaw  | Filius Flitwick    |
-- | 21 | Mandy Brocklehurst     | Ravenclaw  | Filius Flitwick    |
-- | 22 | Marcus Flint           | Slytherin  | Severus Snape      |
-- | 23 | Marietta Edgecombe     | Ravenclaw  | Filius Flitwick    |
-- | 24 | Michael Corner         | Ravenclaw  | Filius Flitwick    |
-- | 25 | Millicent Bulstrode    | Slytherin  | Severus Snape      |
-- | 26 | Neville Longbottom     | Gryffindor | Minerva McGonagall |
-- | 27 | Padma Patil            | Ravenclaw  | Filius Flitwick    |
-- | 28 | Pansy Parkinson        | Slytherin  | Severus Snape      |
-- | 29 | Parvati Patil          | Gryffindor | Minerva McGonagall |
-- | 30 | Penelope Clearwater    | Ravenclaw  | Filius Flitwick    |
-- | 31 | Robert Hilliard        | Ravenclaw  | Filius Flitwick    |
-- | 32 | Roger Davies           | Ravenclaw  | Filius Flitwick    |
-- | 33 | Romilda Vane           | Gryffindor | Minerva McGonagall |
-- | 34 | Ronald Bilius Weasley  | Gryffindor | Minerva McGonagall |
-- | 35 | Seamus Finnigan        | Gryffindor | Minerva McGonagall |
-- | 36 | Susan Bones            | Hufflepuff | Pomona Sprout      |
-- | 37 | Terence Higgs          | Slytherin  | Severus Snape      |
-- | 38 | Terry Boot             | Ravenclaw  | Filius Flitwick    |
-- | 39 | Tracey Davis           | Slytherin  | Severus Snape      |
-- | 40 | Vincent Crabbe         | Slytherin  | Severus Snape      |
-- +----+------------------------+------------+--------------------+
-- We are going to move the information in this one big table into two tables linked by a junction table

-- The Students table...
CREATE TABLE students (
    student_id INTEGER NOT NULL,
    student_name TEXT NOT NULL,
    PRIMARY KEY(student_id)
);

-- The Houses table
CREATE TABLE houses (
    house_id INTEGER NOT NULL,
    house_name TEXT NOT NULL,
    house_head_name TEXT NOT NULL,
    PRIMARY KEY(house_id)
);

-- The junction table for the above
CREATE TABLE studentshouses (
    students_houses_id INTEGER NOT NULL,
    FOREIGN KEY(students_houses_id) REFERENCES students(student_id),
    FOREIGN KEY(students_houses_id) REFERENCES houses(house_id)
);
