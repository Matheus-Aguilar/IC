#include <bits/stdc++.h>
using namespace std;

struct Edge1 {
    int label;
    pair<double,double> p0;
    pair<double,double> p1;
    int fPos,fNeg;
};

bool operator<(const Edge1& a, const Edge1& b) {
    if(a.p0 < b.p0)
        return true;
    else if (a.p1 < b.p1)
        return true;
    else if(a.fPos < b.fPos)
        return true;
    return a.fNeg < b.fNeg;
}

struct Edge2 {
    int label;
    int p0;
    int p1;
    int fPos,fNeg;
};

int main() {
    int l,n,v0,v1,fPos,fNeg;
    int nPoints=0,nEdges=0;
    set<Edge1> edges;
    map<pair<double,double> ,int> pointsSet;
    while(cin >> l >> n >> v0 >> v1 >> fPos >> fNeg) {
        pair<double,double> point0,point1;
        Edge1 edge = {-1,{0,0},{0,0},fPos,fNeg};

        cin >> point1.first >> point1.second;
        pointsSet.insert(make_pair(point1,pointsSet.size()));
        edge.p0 = point1;
        for(int i=1; i<n-1; i++) {
            point0 = point1;
            cin >> point1.first >> point1.second;
            pointsSet.insert(make_pair(point1,pointsSet.size()));
            edge.p1 = point1;
            edges.insert(edge);
            edge.p0 = point1;
        }
        point0 = point1;
        cin >> point1.first >> point1.second;
        edge.p0 = point0; edge.p1 = point1;
        pointsSet.insert(make_pair(point1,pointsSet.size()));
        edges.insert(edge);
    }

    cout << pointsSet.size() << "\n";
    int i=0;
    for(auto &c:pointsSet) {
        cout << c.second << " " << c.first.first << " " << c.first.second << "\n";
        //i++;
    }
    i=0; Edge2 out;
    cout << edges.size() << "\n";
    for(auto it = edges.begin(); it != edges.end(); it++, i++) {
        out.label = i;
        out.fPos = (*it).fPos;
        out.fNeg = (*it).fNeg;
        out.p0 = (*pointsSet.find((*it).p0)).second;
        out.p1 = (*pointsSet.find((*it).p1)).second;
        cout << out.label << " " << out.p0 << " " << out.p1 << " " << out.fPos << " " << out.fNeg << "\n";
    }
    return 0;
}
