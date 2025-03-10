SELECT AVG(rating) FROM ratings r JOIN movies m WHERE r.movie_id = m.id AND m.year = 2012;
