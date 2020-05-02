#include <iostream>
#include <cstdio>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_3 Point_3;

struct Point{
    long double x,y,z;
};

int main(int argc, char* argv[]) {
    
    int n;
    cin >> n;

    string table = argv[1];
    //1 - Segments, 2 - Triangles
    int type = atoi(argv[2]);
    
    printf("CREATE TABLE IF NOT EXISTS %s(id bigserial, geom geometry(GeometryZ));\n", table.c_str());
    printf("INSERT INTO %s(geom) VALUES \n", table.c_str());

    vector<Point> p(n);

    for(int i = 0; i < n; i++){
        scanf("%Lf%Lf%Lf", &p[i].x, &p[i].y, &p[i].z);
    }

    cin >> n;
    n = min(n, atoi(argv[3]));

    for(int i = 0; i < n; i++){
        if(type == 1){
            int id1, id2;
            scanf("%d%d", &id1, &id2);
            printf("(\'LINESTRINGZ(%.15Lf %.15Lf %.15Lf, %.15Lf %.15Lf %.15Lf)\')%s\n", 
            p[id1].x, p[id1].y, p[id1].z, 
            p[id2].x, p[id2].y, p[id2].z, 
            (i != n - 1 ? "," : ";"));
        }
        else{
            int id1, id2, id3;
            scanf("%d%d%d", &id1, &id2, &id3);

            if(CGAL::collinear(Point_3(p[id1].x, p[id1].y, p[id1].z), Point_3(p[id2].x, p[id2].y, p[id2].z), Point_3(p[id3].x, p[id3].y, p[id3].z))) continue;

            printf("(\'POLYGONZ((%.15Lf %.15Lf %.15Lf, %.15Lf %.15Lf %.15Lf, %.15Lf %.15Lf %.15Lf, %.15Lf %.15Lf %.15Lf))\')%s\n", 
            p[id1].x, p[id1].y, p[id1].z, p[id2].x, 
            p[id2].y, p[id2].z, p[id3].x, p[id3].y, 
            p[id3].z, p[id1].x, p[id1].y, p[id1].z, 
            (i != n - 1 ? "," : ";"));
        }
    }

    printf("CREATE INDEX IF NOT EXISTS %s_id_idx ON %s(id);\n", table.c_str(), table.c_str());
    printf("CREATE INDEX IF NOT EXISTS %s_geom_idx ON %s USING GIST(geom);", table.c_str(), table.c_str());
}