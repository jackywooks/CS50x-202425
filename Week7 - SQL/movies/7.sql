SELECT title, rating FROM movies m JOIN ratings r WHERE m.id = r.movie_id AND year = 2010 ORDER BY rating DESC, title LIMIT 10;
