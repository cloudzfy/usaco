/*
 ID: cloudzf2
 PROG: fence4
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
    bool operator==(const point &a) {
        return fabs(x - a.x) < EPS && fabs(y - a.y) < EPS;
    }
};

double cross(point &a, point &b, point &c) {
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

double isIntersect1(point &a, point &b, point &c, point &d) {
    return cross(a, b, c) * cross(a, b, d) < -EPS && cross(c, d, a) * cross(c, d, b) < -EPS;
}

double isIntersect2(point &a, point &b, point &c, point &d) {
    return cross(a, b, c) * cross(a, b, d) < EPS && cross(c, d, a) * cross(c, d, b) < EPS;
}

bool validateFence(vector<point> &fence) {
    int N = (int)fence.size();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            if (isIntersect1(fence[i], fence[(i + 1) % N], fence[j], fence[(j + 1) % N])) return false;
        }
    }
    return true;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("fence4.in");
    ofstream fout ("fence4.out");
    int N;
    double x, y;
    fin >> N >> x >> y;
    point observer(x, y);
    vector<point> fence;
    for (int i = 0; i < N; i++) {
        fin >> x >> y;
        fence.push_back(point(x, y));
    }
    if (!validateFence(fence)) {
        fout << "NOFENCE" << endl;
        return 0;
    }
    vector<bool> visited(N, false);
    for (int i = 0; i < N; i++) {
        point tmp = fence[i];
        double dx = (fence[(i + 1) % N].x - fence[i].x) / 500;
        double dy = (fence[(i + 1) % N].y - fence[i].y) / 500;
        for (int j = 1; j < 500; j++) {
            tmp.x += dx;
            tmp.y += dy;
            bool isCovered = false;
            for (int k = 0; k < N; k++) {
                if (i == k) continue;
                if (isIntersect2(observer, tmp, fence[k], fence[(k + 1) % N])) {
                    isCovered = true;
                    break;
                }
            }
            if (!isCovered) {
                visited[i] = true;
                break;
            }
        }
    }
    vector<pair<point, point> > ans;
    for (int i = 0; i < N - 2; i++) {
        if (visited[i] && cross(observer, fence[i], fence[i + 1]) != 0) {
            ans.push_back(make_pair(fence[i], fence[i + 1]));
        }
    }
    if (visited[N - 1] && cross(observer, fence[N - 1], fence[0]) != 0) {
        ans.push_back(make_pair(fence[0], fence[N - 1]));
    }
    if (visited[N - 2] && cross(observer, fence[N - 2], fence[N - 1]) != 0) {
        ans.push_back(make_pair(fence[N - 2], fence[N - 1]));
    }
    fout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        fout << ans[i].first.x << " " << ans[i].first.y << " " << ans[i].second.x << " " << ans[i].second.y << endl;
    }
    return 0;
}
