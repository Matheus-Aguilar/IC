CREATE TABLE IF NOT EXISTS trianglesFromShapes(id bigserial, shape_id bigserial, geom geometry(GeometryZ));

INSERT INTO trianglesfromshapes(shape_id, geom) 
(
    SELECT id, (st_dump(geom)).geom 
    FROM geological_shapes
);


