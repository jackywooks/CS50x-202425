SELECT name FROM people p JOIN stars s ON p.id = s.person_id WHERE s.movie_id in (SELECT s1.movie_id FROM movies m1 JOIN stars s1 ON m1.id = s1.movie_id JOIN people p1 ON s1.person_id = p1.id WHERE p1.name = "Kevin Bacon") AND p.name != "Kevin Bacon";

