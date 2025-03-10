SELECT title from movies m JOIN stars s ON m.id = s.movie_id JOIN people p ON p.id = s.person_id JOIN ratings r ON m.id = r.movie_id WHERE p.name = "Chadwick Boseman" ORDER by rating DESC LIMIT 5;
