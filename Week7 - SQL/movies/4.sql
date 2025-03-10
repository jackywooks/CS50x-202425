SELECT count(*) FROM movies m JOIN ratings r WHERE m.id = r.movie_id AND rating = 10;
