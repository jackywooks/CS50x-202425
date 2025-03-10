SELECT title FROM movies m JOIN stars s ON m.id = s.movie_id
JOIN people p ON s.person_id = p.id
WHERE p.name in ("Bradley Cooper") AND m.id in (SELECT m.id FROM movies m JOIN stars s ON m.id = s.movie_id
JOIN people p ON s.person_id = p.id
WHERE p.name in ("Jennifer Lawrence") );
