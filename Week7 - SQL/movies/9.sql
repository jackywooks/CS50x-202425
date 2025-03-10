SELECT name from people p JOIN stars s ON p.id = s.person_id JOIN movies m ON s.movie_id = m.id WHERE m.year = 2004 GROUP BY p.id ORDER BY p.birth ;
