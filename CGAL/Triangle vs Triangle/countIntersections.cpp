#include<iostream>
#include<fstream>
#include<vector>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/intersections.h>
#include<CGAL/Bbox_3.h>

using namespace std;

//How to compile: g++ countIntersections.cpp -O3 -lCGAL -lgmp

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Point_3<Kernel> Point;
typedef CGAL::Triangle_3<Kernel> Triangle;
typedef CGAL::Bbox_3 Bbox;

int main(int argc, char **argv){
    
	if(argc != 3){
		cout << "How to execute: ./a.out file1 file2" << "\n";
		return 0;
	}

    ifstream f1(argv[1]), f2(argv[2]);
    
    int np1, np2, nt1, nt2;

    f1 >> np1;
    f2 >> np2;

    vector<Point> p1(np1), p2(np2);

    //Points from file 1
    for(int i = 0; i < np1; i++){
    	double x, y, z;
    	f1 >> x >> y >> z;
    	p1[i] = Point(x, y, z);
    }

    //Points from file 2
    for(int i = 0; i < np2; i++){
    	double x, y, z;
    	f2 >> x >> y >> z;
    	p2[i] = Point(x, y, z);
    }

    f1 >> nt1;
    f2 >> nt2;

    vector<Triangle> t1(nt1), t2(nt2);
    vector<Bbox> b1(nt1), b2(nt2);

    //Triangles from file 1
    for(int i = 0; i < nt1; i++){
    	int id1, id2, id3;
    	f1 >> id1 >> id2 >> id3;
    	t1[i] = Triangle(p1[id1], p1[id2], p1[id3]);
        b1[i] = t1[i].bbox();
    }

    //Triangles from file 2
    for(int i = 0; i < nt2; i++){
    	int id1, id2, id3;
    	f2 >> id1 >> id2 >> id3;
    	t2[i] = Triangle(p2[id1], p2[id2], p2[id3]);
        b2[i] = t2[i].bbox();
    }

    //Pairs of intersections
    vector<pair<int, int>> inter;

    for(int i = 0; i < nt1; i++){
        for(int j = 0; j < nt2; j++){
            if(CGAL::do_overlap(b1[i], b2[j]) && CGAL::do_intersect(t1[i], t2[j])){
                inter.emplace_back(i, j);
            }
        }
    }

    cout << inter.size() << "\n\n";

    for(int i = 0; i < inter.size(); i++)
        cout << inter[i].first << " " << inter[i].second << "\n";
}