-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT * FROM crime_scene_reports WHERE year = 2023 AND month = 7 AND day = 28 AND street = "Humphrey Street";

-- case no. 295
-- | 295 | 2023 | 7     | 28  | Humphrey Street |
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time –
--  each of their interview transcripts mentions the bakery. |

SELECT * FROM interviews WHERE year = 2023 AND month = 7 AND day = 28 AND transcript like "%bakery%";
-- | 161 | Ruth    | 2023 | 7     | 28  |
-- Sometime within ten minutes of the theft,
-- I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot,
-- you might want to look for cars that left the parking lot in that time frame.|
SELECT * FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;
-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | id  | year | month | day | hour | minute | activity | license_plate |
-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | 260 | 2023 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
-- | 261 | 2023 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
-- | 262 | 2023 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
-- | 263 | 2023 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
-- | 264 | 2023 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
-- | 265 | 2023 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
-- | 266 | 2023 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
-- | 267 | 2023 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
-- +-----+------+-------+-----+------+--------+----------+---------------+


-- | 162 | Eugene  | 2023 | 7     | 28  |
-- I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at Emma's bakery,
-- I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
SELECT * from atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+
-- | id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+
-- | 246 | 28500762       | 2023 | 7     | 28  | Leggett Street | withdraw         | 48     |
-- | 264 | 28296815       | 2023 | 7     | 28  | Leggett Street | withdraw         | 20     |
-- | 266 | 76054385       | 2023 | 7     | 28  | Leggett Street | withdraw         | 60     |
-- | 267 | 49610011       | 2023 | 7     | 28  | Leggett Street | withdraw         | 50     |
-- | 269 | 16153065       | 2023 | 7     | 28  | Leggett Street | withdraw         | 80     |
-- | 288 | 25506511       | 2023 | 7     | 28  | Leggett Street | withdraw         | 20     |
-- | 313 | 81061156       | 2023 | 7     | 28  | Leggett Street | withdraw         | 30     |
-- | 336 | 26013199       | 2023 | 7     | 28  | Leggett Street | withdraw         | 35     |
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+

-- | 163 | Raymond | 2023 | 7     | 28  |
-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket. |
SELECT * FROM phone_calls WHERE  year = 2023 AND month = 7 AND day = 28 AND duration < 60;
-- +-----+----------------+----------------+------+-------+-----+----------+
-- | id  |     caller     |    receiver    | year | month | day | duration |
-- +-----+----------------+----------------+------+-------+-----+----------+
-- | 221 | (130) 555-0289 | (996) 555-8899 | 2023 | 7     | 28  | 51       |
-- | 224 | (499) 555-9472 | (892) 555-8872 | 2023 | 7     | 28  | 36       |
-- | 233 | (367) 555-5533 | (375) 555-8161 | 2023 | 7     | 28  | 45       |
-- | 251 | (499) 555-9472 | (717) 555-1342 | 2023 | 7     | 28  | 50       |
-- | 254 | (286) 555-6063 | (676) 555-6554 | 2023 | 7     | 28  | 43       |
-- | 255 | (770) 555-1861 | (725) 555-3243 | 2023 | 7     | 28  | 49       |
-- | 261 | (031) 555-6622 | (910) 555-3251 | 2023 | 7     | 28  | 38       |
-- | 279 | (826) 555-1652 | (066) 555-9701 | 2023 | 7     | 28  | 55       |
-- | 281 | (338) 555-6650 | (704) 555-2131 | 2023 | 7     | 28  | 54       |
-- +-----+----------------+----------------+------+-------+-----+----------+


SELECT * FROM people WHERE license_plate in
(SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25)
AND phone_number in
-- Find the
(SELECT caller FROM phone_calls WHERE  year = 2023 AND month = 7 AND day = 28 AND duration < 60)
AND id in
-- Find the person id of the account
(SELECT person_id FROM bank_accounts WHERE account_number in
(SELECT account_number from atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"));

-- Result of person who withdrew, call under 60s, and have the car left the bakery that day
-- +--------+-------+----------------+-----------------+---------------+
-- |   id   | name  |  phone_number  | passport_number | license_plate |
-- +--------+-------+----------------+-----------------+---------------+
-- | 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+-------+----------------+-----------------+---------------+


-- Finding the suspect's flight
SELECT * FROM passengers WHERE passport_number in (
    SELECT passport_number FROM people WHERE license_plate in
    (
        SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25
    )
    AND phone_number in
    (
        SELECT caller FROM phone_calls WHERE  year = 2023 AND month = 7 AND day = 28 AND duration < 60
    )
    AND id in
    (
        SELECT person_id FROM bank_accounts WHERE account_number in
        (
            SELECT account_number from atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"
        )
    )
);
-- Suspect Passport Number and result
-- +-----------+-----------------+------+
-- | flight_id | passport_number | seat |
-- +-----------+-----------------+------+
-- | 18        | 3592750733      | 4C   |
-- | 24        | 3592750733      | 2C   |
-- | 36        | 5773159633      | 4A   |
-- | 54        | 3592750733      | 6C   |
-- +-----------+-----------------+------+


SELECT *FROM flights WHERE id in (
    SELECT flight_id FROM passengers WHERE passport_number in (
        SELECT passport_number FROM people WHERE license_plate in
        (
            SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25
        )
        AND phone_number in
        (
            SELECT caller FROM phone_calls WHERE  year = 2023 AND month = 7 AND day = 28 AND duration < 60
        )
        AND id in
        (
            SELECT person_id FROM bank_accounts WHERE account_number in
            (
                SELECT account_number from atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"
            )
        )
    )
) AND year = 2023 AND month = 7 AND day = 28 + 1 AND hour < 12;
-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | 36 | 8                 | 4                      | 2023 | 7     | 29  | 8    | 20     |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+

-- suspect is Bruce
SELECT * FROM airports WHERE id = 4;
-- +----+--------------+-------------------+---------------+
-- | id | abbreviation |     full_name     |     city      |
-- +----+--------------+-------------------+---------------+
-- | 4  | LGA          | LaGuardia Airport | New York City |
-- +----+--------------+-------------------+---------------+

-- city he flee is New York City


-- Finding the accomplice after narrowing down the suspect
SELECT * FROM people WHERE phone_number in (
    SELECT receiver FROM phone_calls WHERE caller in (
        SELECT phone_number FROM people WHERE license_plate in
        (
            SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25
        )
        AND phone_number in
        (
            SELECT caller FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60
        )
        AND id in
        (
            SELECT person_id FROM bank_accounts WHERE account_number in
            (
                SELECT account_number from atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"
            )
        )
    ) AND duration < 60 AND year = 2023 AND month = 7 AND day = 28
);
-- +--------+--------+----------------+-----------------+---------------+
-- |   id   |  name  |  phone_number  | passport_number | license_plate |
-- +--------+--------+----------------+-----------------+---------------+
-- | 847116 | Philip | (725) 555-3243 | 3391710505      | GW362R6       |
-- | 864400 | Robin  | (375) 555-8161 | NULL            | 4V16VO0       |
-- +--------+--------+----------------+-----------------+---------------+


-- accomplice is Robin
