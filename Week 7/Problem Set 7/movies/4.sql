SELECT COUNT(movie_id)
FROM (SELECT movie_id FROM ratings WHERE rating = 10.0);