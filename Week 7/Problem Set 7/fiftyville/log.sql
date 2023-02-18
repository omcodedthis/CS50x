-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get the crime scene report of the theft
SELECT description FROM crime_scene_reports WHERE (year = 2021 AND month = 7 AND day =28);

-- Get eyewitnesses report on the theft
SELECT transcript FROM interviews WHERE (year = 2021 AND month = 7 AND day =28);

-- Get activity at time of theft from the Bakery
SELECT activity FROM bakery_security_logs WHERE (year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute < 15);

-- Get the call logs at the time of the theft that were shorter than 60s
SELECT id, caller, receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;

-- The phone_numbers of the caller & reciever from the logs derived above
SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;
SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;

-- Full names of all the airports
SELECT * FROM airports;

-- Flight details of the very first flight out of Fiftyville on 29 July 2021
SELECT id, origin_airport_id, destination_airport_id, hour  FROM flights WHERE year = 2021 AND month = 7 AND day = 29 ORDER BY hour;

-- Passport numbers of the passengers on this flight
SELECT passport_number FROM passengers WHERE flight_id = 36;

-- Names of the people on the flight
SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);

-- License plates of the cars at the Bakery before 11am
SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour < 11;

-- Names of the owners of cars with the above license plates
SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour < 11);

-- Person IDs of the bank accounts that were involved in the transactions at the atm at Leggett Street on the day of the theft
SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street");

-- The names of the owners of these phone numbers
SELECT name FROM people where phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60);

-- The transaction details of the people who had withdraw money at Leggett Street before the theft
SELECT account_number, transaction_type, amount  FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street";

-- The receiver of the call by the first main suspect, Bruce:
SELECT name FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE caller = (SELECT phone_number FROM people WHERE name = "Bruce" AND year = 2021 AND month = 7 AND day = 28 AND duration < 60));
-- Robin

-- The receiver of the call by the second main suspect, Taylor:
SELECT name FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE caller = (SELECT phone_number FROM people WHERE name = "Taylor" AND year = 2021 AND month = 7 AND day = 28 AND duration < 60));
-- James

--Notes:
-- Suspects:
-- Kenny, Sofia, Taylor, Kelsey, Bruce, Doris, Robin.

-- The Thief: Bruce, as he was the only person that withdrew money before the theft, used a car at the bakery (license plate linked) at
-- the bakery near the time of the theft, was a caller of a call that lasted less than a minute at hour of the theft andwas a passenger
-- on the first plane out of Fiftyvile on 29 July 2021.

-- The Accomplice: Robin, he was the only person that also used a car at the bakery (license plate linked) that was at the bakery near at
-- the time of the theft and was a receiver of a call that lasted less than a minute.

-- The others were ruled out as they either did not use a car at the bakery (license plate linked) near the time of the theft or was not
-- part of a caller-receiver pair of a call that lasted less than a min by a suspected caller.