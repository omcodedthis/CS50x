"SQL Statement for cleaning up "How I Met Your Mother" titles:"
UPDATE shows SET title = "How I Met Your Mother" WHERE title = "How i met your mother";


"SQL Statements for cleaning up "Brooklyn Nine-Nine" titles:"
UPDATE shows SET title = 'Brooklyn Nine-Nine' WHERE title LIKE 'Brook%';
UPDATE shows SET title = 'Brooklyn Nine-Nine' WHERE title = 'B99';


"SQL Statement for cleaning up "Game of Thrones" titles:"
UPDATE shows SET title = 'Game of Thrones' WHERE title = 'GoT';


"SQL Statement for cleaning up "Grey's Anatomy" titles:"
UPDATE shows SET title = "Grey's Anatomy" WHERE title LIKE "Gre%";


"SQL Statement for cleaning up "It’s Always Sunny in Philadelphia" titles:"
UPDATE shows SET title = "It’s Always Sunny in Philadelphia" WHERE title = "Its Always Sunny in Philidelphia";


SQL Statement for cleaning up "Parks and Recreation" titles:
UPDATE shows SET title = "Parks and Recreation" WHERE title LIKE "Pa%";


"SQL Statements for cleaning up "The Office" titles:"
UPDATE shows SET title = "The Office" WHERE title LIKE "The O%";
UPDATE shows SET title = "The Originals" WHERE id = 127;