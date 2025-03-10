SELECT AVG(energy) as average_energy FROM songs WHERE artist_id in (SELECT id FROM artists WHERE name = "Drake");
