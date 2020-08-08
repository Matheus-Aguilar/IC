SELECT COUNT(*) 
FROM segments s, geological_shapes g 
WHERE g.geom && s.geom AND EXISTS(
    SELECT 1 
    FROM trianglesFromShapes t 
    WHERE t.shape_id = g.id AND _st_3dintersects(t.geom, s.geom)
);

