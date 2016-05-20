/*
 ID: cloudzf2
 PROG: fc
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

#define eps 1e-8

struct point {
    double x, y;
    double angle;
    point(double x, double y) : x(x), y(y) {}
};

bool cmp(const point &a, const point &b) {
    return a.angle < b.angle;
}

double cross(point a, point b, point c) {
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

double dist(point a, point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main(int argc, const char * argv[]) {
    ifstream fin ("fc.in");
    ofstream fout ("fc.out");
    int N;
    double x, y;
    fin >> N;
    vector<point> points;
    point mid(0, 0);
    for (int i = 0; i < N; i++) {
        fin >> x >> y;
        mid.x += x / N;
        mid.y += y / N;
        points.push_back(point(x, y));
    }
    if (N < 2) {
        fout << 0.00 << endl;
        return 0;
    }
    for (int i = 0; i < N; i++) {
        points[i].angle = atan2(points[i].y - mid.y, points[i].x - mid.x + eps);
    }
    sort(points.begin(), points.end(), cmp);
    deque<point> ans;
    ans.push_back(points[0]);
    ans.push_back(points[1]);
    for (int i = 2; i < N; i++) {
        while (ans.size() >= 2 && cross(ans[(int)ans.size() - 2], ans[(int)ans.size() - 1], points[i]) < -eps) {
            ans.pop_back();
        }
        ans.push_back(points[i]);
    }
    while (true) {
        if (ans.size() >= 3 && cross(ans[(int)ans.size() - 2], ans[(int)ans.size() - 1], ans[0]) < -eps) {
            ans.pop_back();
            continue;
        }
        if (ans.size() >= 3 && cross(ans[(int)ans.size() - 1], ans[0], ans[1]) < -eps) {
            ans.pop_front();
            continue;
        }
        break;
    }
    double len = 0;
    int M = (int)ans.size();
    for (int i = 0; i < M; i++) {
        len += dist(ans[i], ans[(i + 1) % M]);
    }
    fout << setiosflags(ios::fixed) << setprecision(2) << len << endl;
    return 0;
}
