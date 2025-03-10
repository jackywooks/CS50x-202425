SELECT name from people p JOIN directors d ON p.id = d.person_id JOIN ratings r ON r.movie_id = d.movie_id WHERE r.rating >= 9 GROUP BY d.person_id;
