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
#include <CGAL/Exact_rational.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;

typedef Kernel::Point_2 Point;

typedef Kernel::Segment_2 Segment2;
typedef pair<int, Segment2> Segment;

typedef CGAL::Box_intersection_d::Box_with_handle_d<double,2,vector<Segment>::iterator> Box;

int cont1 = 0;
int cont2 = 0;

vector<pair<Segment2 *, Segment2 *>> possibleIntersections;

void callback1( const Box& a, const Box& b ) {
    cont1++;
}


void callback2( const Box& a, const Box& b ) {
    possibleIntersections[cont1++] = make_pair(&(a.handle()->second), &(b.handle()->second));
}

int main(int argc, char* argv[]) {
    
    ifstream f1, f2;
    
    f1.open(argv[1]);
    f2.open(argv[2]);
    
    int nP1, nP2, nE1, nE2;
    
    map <int, Point> points1;
    map <int, Point> points2;
    
    vector<Segment> edges1;
    vector<Segment> edges2;
    
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
        edges1.push_back(make_pair(idEdge, Segment2(points1[idPoint1], points1[idPoint2])));
    }

    for(auto it = edges1.begin(); it != edges1.end(); it++)
        bbox1.push_back(Box(it->second.bbox(), it));

    f2 >> nP2;

    for(int i = 0; i < nP2; i++){
        int id;
        double x, y;
        f2 >> id >> x >> y;
        points2[id] = Point(x, y);
    }


    f2 >> nE2;

    for(int i = 0; i < nE2; i++){
        int idEdge, idPoint1, idPoint2, aux;
        f2 >> idEdge >> idPoint1 >> idPoint2 >> aux >> aux;
        edges2.push_back(make_pair(idEdge, Segment2(points2[idPoint1], points2[idPoint2])));
    }

    for(auto it = edges2.begin(); it != edges2.end(); it++)
        bbox2.push_back(Box(it->second.bbox(), it));
    
    double t = time(0);

    CGAL::box_intersection_d(bbox1.begin(), bbox1.end(), bbox2.begin(), bbox2.end(), callback1);

    possibleIntersections.resize(cont1);
    cont1 = 0;
    
    auto start = chrono::steady_clock::now();

    CGAL::box_intersection_d(bbox1.begin(), bbox1.end(), bbox2.begin(), bbox2.end(), callback2);

    auto end = chrono::steady_clock::now();

    auto start2 = chrono::steady_clock::now();

    for(int i = 0; i < cont1; i++)
        if(CGAL::do_intersect(*possibleIntersections[i].first, *possibleIntersections[i].second))
            cont2++;

    auto end2 = chrono::steady_clock::now();


    cout << "Tempo da filtragem por bounding box: " << chrono::duration_cast<chrono::milliseconds>(end - start).count()/1000.0 << " s\n";
    cout << "Tempo dos testes de intersecao: " << chrono::duration_cast<chrono::milliseconds>(end2 - start2).count()/1000.0 << " s\n";
    cout << "Número de Testes de intersecoes: " << cont1 << "\n";
    cout << "Número de Intersecoes: " << cont2 << "\n";

    #ifdef _SHOW_EDGES
        for(int i = 0; i < cont1; i++)
            if(CGAL::do_intersect(*possibleIntersections[i].first, *possibleIntersections[i].second)){
                cout << "(" << possibleIntersections[i].first->min() << "," << possibleIntersections[i].first->max()  << ") ";
                cout << "(" << possibleIntersections[i].second->min() << "," << possibleIntersections[i].second->max() << ")\n";
            }
    #endif

    f1.close();
    f2.close();
}