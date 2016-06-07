/*
 ID: cloudzf2
 PROG: fence3
 LANG: C++11
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <set>
#include <map>
#include <iomanip>
#include <stack>
#include <cmath>

using namespace std;

#define INF 2147483647
#define EPS 1e-8

struct point {
    double x, y;
    point(double x, double y) : x(x), y(y) {}
    point operator-(const point &a) {
        return point(x - a.x, y - a.y);
    }
    bool operator==(const point &a) {
        return x == a.x && y == a.y;
    }
};

struct line {
    double x1, y1, x2, y2;
    line(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
    point end1() {return point(x1, y1);}
    point end2() {return point(x2, y2);}
};

double direction[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

double cross(point a, point b, point c) {
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

double dot(point a, point b, point c) {
    return (b.x - a.x) * (c.x - a.x) + (b.y - a.y) * (c.y - a.y);
}

double length(point a, point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double dist(point p, line l) {
    if (l.end1() == l.end2()) return length(p, l.end1());
    if (dot(l.end1(), l.end2(), p) < 0) return length(l.end1(), p);
    else if (dot(l.end2(), l.end1(), p) < 0) return length(l.end2(), p);
    else return fabs(cross(l.end1(), l.end2(), p)) / length(l.end1(), l.end2());
}

int main(int argc, const char * argv[]) {
    ifstream fin ("fence3.in");
    ofstream fout ("fence3.out");
    int F;
    fin >> F;
    int x1, y1, x2, y2;
    vector<line> fence;
    for (int i = 0; i < F; i++) {
        fin >> x1 >> y1 >> x2 >> y2;
        fence.push_back(line(x1, y1, x2, y2));
    }
    double T = 100;
    point p = fence[0].end1();
    double ans = INF;
    double delta = 0.98;
    while (T > EPS) {
        bool isValid = true;
        while (isValid) {
            isValid = false;
            for (int i = 0; i < 4; i++) {
                point tmp(p.x + direction[i][0] * T, p.y + direction[i][1] * T);
                double myans = 0;
                for (int j = 0; j < F; j++) {
                    myans += dist(tmp, fence[j]);
                }
                if (myans < ans) {
                    ans = myans;
                    p = tmp;
                    isValid = true;
                }
            }
        }
        T *= delta;
    }
    fout.setf(ios::fixed);
    fout << setprecision(1) << (double)p.x << " " << (double)p.y << " " << ans << endl;
    return 0;
}
