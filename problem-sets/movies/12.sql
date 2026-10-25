-- 12. Titles of all of movies in which both Jennifer Lawrence and Bradley Cooper starred
select movies.title FROM movies
JOIN stars AS jennifer_lawrence_stars ON movies.id = jennifer_lawrence_stars.movie_id
JOIN people AS jennifer_lawrence ON jennifer_lawrence_stars.person_id = jennifer_lawrence.id
JOIN stars AS bradley_cooper_stars ON movies.id = bradley_cooper_stars.movie_id
JOIN people AS bradley_cooper ON bradley_cooper_stars.person_id = bradley_cooper.id
WHERE jennifer_lawrence.name = 'Jennifer Lawrence' AND bradley_cooper.name = 'Bradley Cooper';


