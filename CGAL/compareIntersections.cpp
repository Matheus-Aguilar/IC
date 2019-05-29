#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <chrono>
#include <CGAL/box_intersection_d.h>
#include <CGAL/Bbox_2.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Exact_rational.h>
#include <CGAL/Simple_cartesian.h>

using namespace std;

typedef CGAL::Box_intersection_d::Box_d<double,2> Box;
typedef CGAL::Bbox_2 Bbox;
typedef CGAL::Point_2<CGAL::Cartesian <double>> Point;
typedef CGAL::Segment_2<CGAL::Cartesian <double>> Segment;

int cont1 = 0;
int contt2 = 0;

void callback( const Box& a, const Box& b ) {
    cont1++;
}
int main(int argc, char* argv[]) {
    
    
    ifstream f1, f2;
    
    f1.open(argv[1]);
    f2.open(argv[2]);
    
    int nP1, nP2, nE1, nE2;
    map <int, Point> points1;
    map <int, Point> points2;
    map<int, Segment> edges1;
    map<int, Segment> edges2;
    vector<Box> bbox1;
    vector<Box> bbox2;

    f1 >> nP1;

    for(int i = 0; i < nP1; i++){
        int id;
        double x, y;
        f1 >> id >> x >> y;
        points1[id] = Point(x, y);
    }

    f1 >> nE1;

    for(int i = 0; i < nE1; i++){
        int idEdge, idPoint1, idPoint2, aux;
        f1 >> idEdge >> idPoint1 >> idPoint2 >> aux >> aux;
        edges1[idEdge] = Segment(points1[idPoint1], points1[idPoint2]);
        bbox1.push_back(Bbox(
            fmin(points1[idPoint1].hx(), points1[idPoint2].hx()), 
            fmin(points1[idPoint1].hy(), points1[idPoint2].hy()),
            fmax(points1[idPoint1].hx(), points1[idPoint2].hx()),
            fmax(points1[idPoint1].hy(), points1[idPoint2].hy())
        ));
    }

    f1 >> nP1;

    for(int i = 0; i < nP1; i++){
        int id;
        double x, y;
        f1 >> id >> x >> y;
        points1[id] = Point(x, y);
    }

    f2 >> nE2;

    for(int i = 0; i < nE2; i++){
        int idEdge, idPoint1, idPoint2, aux;
        f2 >> idEdge >> idPoint1 >> idPoint2 >> aux >> aux;
        edges2[idEdge] = Segment(points2[idPoint1], points2[idPoint2]);
        bbox2.push_back(Bbox(
            fmin(points2[idPoint1].hx(), points2[idPoint2].hx()), 
            fmin(points2[idPoint1].hy(), points2[idPoint2].hy()),
            fmax(points2[idPoint1].hx(), points2[idPoint2].hx()),
            fmax(points2[idPoint1].hy(), points2[idPoint2].hy())
        ));
    }

    double t = time(0);

    auto start = chrono::steady_clock::now();

    CGAL::box_intersection_d(bbox1.begin(), bbox1.end(), bbox1.begin(), bbox1.end(), callback);

    auto end = chrono::steady_clock::now();

    cout << "Tempo: " << chrono::duration_cast<chrono::milliseconds>(end - start).count()/1000.0 << " s\n";
    cout << "Número de Testes " << cont1 << "\n";

    f1.close();
    f2.close();
}