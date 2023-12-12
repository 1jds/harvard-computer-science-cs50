-- Keep a log of any SQL queries you execute as you solve the mystery.

-- I am going to start by looking at the crime scene reports for the time and place in question
SELECT * FROM crime_scene_reports WHERE street = "Humphrey Street" AND month = 7 AND day = 28;
-- +-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | id  | year | month | day |     street      |                                                                                                       description                                                                                                        |
-- +-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | 295 | 2021 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
-- | 297 | 2021 | 7     | 28  | Humphrey Street | Littering took place at 16:36. No known witnesses.                                                                                                                                                                       |
-- +-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

-- I could go now to the bakery info or the witness transcripts. I think I'll start with the witnesses and see if I can find the relevant witnesses
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";
-- +-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | id  |  name   | year | month | day |                                                                                                                                                     transcript                                                                                                                                                      |
-- +-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- | 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- | 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
-- +-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

-- Since the witness Raymond says that they were planning to take "the earliest flight out of Fiftyville tomorrow", I might be able to find out their destination by looking for the earliest flight out of Fiftyville on the 29th July and see what its location was
SELECT * FROM flights JOIN airports ON flights.destination_airport_id = airports.id WHERE year = 2021 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1;
-- +----+-------------------+------------------------+------+-------+-----+------+--------+----+--------------+-------------------------------------+---------------+
-- | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | id | abbreviation |              full_name              |     city      |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+----+--------------+-------------------------------------+---------------+
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 4  | LGA          | LaGuardia Airport                   | New York City |
-- | 43 | 8                 | 1                      | 2021 | 7     | 29  | 9    | 30     | 1  | ORD          | O'Hare International Airport        | Chicago       |
-- | 23 | 8                 | 11                     | 2021 | 7     | 29  | 12   | 15     | 11 | SFO          | San Francisco International Airport | San Francisco |
-- | 53 | 8                 | 9                      | 2021 | 7     | 29  | 15   | 20     | 9  | HND          | Tokyo International Airport         | Tokyo         |
-- | 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      | 6  | BOS          | Logan International Airport         | Boston        |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+----+--------------+-------------------------------------+---------------+
-- Here, because the earliest flight out of Fiftyville was going to New York City, that is likely the answer to the second question (unless the thieves changed their plan somewhere along the way)

-- Since Raymond says that "As the thief was leaving the bakery, they called someone who talked to them for less than a minute."
-- I might be able to check the call logs and filter for calls less than a minute.
SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 ORDER BY duration;

SELECT * FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 ORDER BY duration);
-- So, the caller (and, hence, the thief) has to have been one of the following people:
-- +--------+---------+----------------+-----------------+---------------+
-- |   id   |  name   |  phone_number  | passport_number | license_plate |
-- +--------+---------+----------------+-----------------+---------------+
-- | 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
-- | 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
-- | 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
-- | 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
-- | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
-- | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
-- | 907148 | Carina  | (031) 555-6622 | 9628244268      | Q12B3Z3       |
-- +--------+---------+----------------+-----------------+---------------+

SELECT * FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 ORDER BY duration);
-- The receiver (and, hence, the accomplice) has to have been one of the following people:
-- +--------+------------+----------------+-----------------+---------------+
-- |   id   |    name    |  phone_number  | passport_number | license_plate |
-- +--------+------------+----------------+-----------------+---------------+
-- | 250277 | James      | (676) 555-6554 | 2438825627      | Q13SVG6       |
-- | 251693 | Larry      | (892) 555-8872 | 2312901747      | O268ZZ0       |
-- | 484375 | Anna       | (704) 555-2131 | NULL            | NULL          |
-- | 567218 | Jack       | (996) 555-8899 | 9029462229      | 52R0Y8U       |
-- | 626361 | Melissa    | (717) 555-1342 | 7834357192      | NULL          |
-- | 712712 | Jacqueline | (910) 555-3251 | NULL            | 43V0R5D       |
-- | 847116 | Philip     | (725) 555-3243 | 3391710505      | GW362R6       |
-- | 864400 | Robin      | (375) 555-8161 | NULL            | 4V16VO0       |
-- | 953679 | Doris      | (066) 555-9701 | 7214083635      | M51FA04       |
-- +--------+------------+----------------+-----------------+---------------+

-- Ruth tells us the following in her witness statement:
-- "Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame."
-- So, we can look at the bakery security logs to see which license plates left at that time...

-- We can use the list of possible thieves (and their plate numbers) we obtained before using the phone-call data and cross-reference this with the number plates of the cars that left the parking lot at that time.
SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND activity = "exit" AND license_plate IN (SELECT license_plate FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 ORDER BY duration));
-- When we do this, we get the following:
-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | id  | year | month | day | hour | minute | activity | license_plate |
-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | 249 | 2021 | 7     | 28  | 8    | 50     | exit     | 4V16VO0       |
-- +-----+------+-------+-----+------+--------+----------+---------------+
-- This means that the thief [EDIT: Accomplice?] has the license plate 4V16VO0. That means that the thief [EDIT: Accomplice?] must be: Robin


-- The thief withdrew some money from Legate street before 8:50am
-- "I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at Emma's bakery,
-- I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money."
SELECT * FROM atm_transactions JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number JOIN people ON bank_accounts.person_id = people.id WHERE year = 2021 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Leggett Street";
-- The thief has to be in this list, because the thief withdrew money from the ATM on Leggett Street
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+----------------+-----------+---------------+--------+---------+----------------+-----------------+---------------+
-- | id  | account_number | year | month | day |  atm_location  | transaction_type | amount | account_number | person_id | creation_year |   id   |  name   |  phone_number  | passport_number | license_plate |
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+----------------+-----------+---------------+--------+---------+----------------+-----------------+---------------+
-- | 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     | 49610011       | 686048    | 2010          | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
-- | 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     | 26013199       | 514354    | 2012          | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     | 16153065       | 458378    | 2012          | 458378 | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       |
-- | 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     | 28296815       | 395717    | 2014          | 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
-- | 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     | 25506511       | 396669    | 2014          | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- | 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     | 28500762       | 467400    | 2014          | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     | 76054385       | 449774    | 2015          | 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
-- | 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     | 81061156       | 438727    | 2018          | 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+----------------+-----------+---------------+--------+---------+----------------+-----------------+---------------+


-- If we cross-reference the names of those who used the ATM with the names of callers from earlier, we get this list of suspects for the thief:
-- +--------+---------+----------------+-----------------+---------------+
-- |   id   |  name   |  phone_number  | passport_number | license_plate |
-- +--------+---------+----------------+-----------------+---------------+
-- | 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
-- | 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
-- | 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
-- | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+---------+----------------+-----------------+---------------+

-- can we now check the flight manifest and see who was flying and narrow down the list of possible thieves further.
SELECT * FROM flights JOIN passengers ON flights.id = passengers.flight_id JOIN people ON passengers.passport_number = people.passport_number WHERE year = 2021 AND month = 7 AND day = 29 AND destination_airport_id = 4;
-- +----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+--------+--------+----------------+-----------------+---------------+
-- | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | flight_id | passport_number | seat |   id   |  name  |  phone_number  | passport_number | license_plate |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+--------+--------+----------------+-----------------+---------------+
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 7214083635      | 2A   | 953679 | Doris  | (066) 555-9701 | 7214083635      | M51FA04       |
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 1695452385      | 3B   | 398010 | Sofia  | (130) 555-0289 | 1695452385      | G412CB7       |
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 5773159633      | 4A   | 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 1540955065      | 5C   | 651714 | Edward | (328) 555-1152 | 1540955065      | 130LD9Z       |
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 8294398571      | 6C   | 560886 | Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       |
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 1988161715      | 6D   | 449774 | Taylor | (286) 555-6063 | 1988161715      | 1106N58       |
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 9878712108      | 7A   | 395717 | Kenny  | (826) 555-1652 | 9878712108      | 30G67EN       |
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 8496433585      | 7B   | 467400 | Luca   | (389) 555-5198 | 8496433585      | 4328GD8       |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+--------+--------+----------------+-----------------+---------------+
