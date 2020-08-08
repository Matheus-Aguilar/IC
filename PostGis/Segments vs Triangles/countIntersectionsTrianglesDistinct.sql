SELECT 
COUNT(*) FROM 
(
    SELECT DISTINCT s.id, shape_id 
    FROM trianglesfromshapes AS t, segments AS s 
    WHERE s.geom && t.geom AND _st_3dintersects(s.geom, t.geom)
) AS result;
