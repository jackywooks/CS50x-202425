select language, count(*) as count  from favorites group by problem order by count desc limit 1;

insert into favorites (language, problem) values("SQL","Final");

delete from favorites where Timestamp IS NULL;

UPDATE favorites SET problem = "FiftyVille", language = "SQL";

Delete from favorites;

-- import csv to database
-- .mode csv
-- .import favorites.csv favorites
-- .quit
