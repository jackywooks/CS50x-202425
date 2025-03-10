-- 1-to-1
-- show to rating table
SELECT s.title,r.* FROM shows s JOIN ratings r WHERE s.id = r.show_id AND r.rating>=9.0 AND r.votes>10000 ORDER BY r.rating DESC;

-- 1-to-many
-- show to genre
SELECT title,genre FROM shows JOIN genres ON shows.id = genres.show_id WHERE id = 63881;

-- many-to-many
-- people to stars to shows
-- need 3 tables
 SELECT name FROM people WHERE id IN
   ...> (SELECT person_id FROM stars WHERE show_id IN
   ...>  (SELECT id FROM shows WHERE title = "The Office" AND year = 2005));

SELECT title FROM shows WHERE id IN
   ...> (SELECT show_id FROM stars WHERE person_id =
   ...> (SELECT id FROM people WHERE name = "Steve Carell"));


-- below query is slow, due to the fact that the foreign key are not indexed
-- 2.4s without index
-- 0.001 after index
SELECT title FROM shows
JOIN stars ON shows.id = stars.show_id
JOIN people ON stars.person_id = people.id
WHERE name = "Steve Carell";

CREATE index show_index ON stars (show_id);
CREATE index person_index ON stars (person_id);
CREATE index name_index ON people (name);

-- .timer ON

-- create INDEX
CREATE index title_index ON shows (title);


