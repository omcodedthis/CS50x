SELECT distinct(name)
FROM people
JOIN stars
ON people.id = stars.person_id
JOIN movies
ON stars.movie_id = movies.id
WHERE movies.title IN
               (SELECT DISTINCT(title)
                FROM people
                JOIN stars
                ON people.id = stars.person_id
                JOIN movies
                ON stars.movie_id = movies.id
                WHERE name = "Kevin Bacon" AND people.birth = 1958) AND name != "Kevin Bacon";