SELECT COUNT(*) 
FROM geological_shapes AS g, segments AS s 
WHERE s.geom && g.geom AND _st_3dintersects(s.geom, g.geom);
