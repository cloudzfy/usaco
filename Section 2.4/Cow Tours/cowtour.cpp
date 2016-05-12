/*
 ID: cloudzf2
 PROG: cowtour
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

using namespace std;

#define DOUBLE_MAX 300000000
int stfind(vector<int> &pre, int x) {
    if (pre[x] != x) {
        pre[x] = stfind(pre, pre[x]);
    }
    return pre[x];
}

void stunion(vector<int> &pre, int x, int y) {
    x = stfind(pre, x);
    y = stfind(pre, y);
    if (x != y) pre[x] = y;
}

double getDist(pair<int, int> &a, pair<int, int> &b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

void floyd(vector<string> &maps, vector<pair<int, int> > &points, vector<double> &path) {
    int N = (int)maps.size();
    vector<vector<double> > dist(N, vector<double>(N, DOUBLE_MAX));
    for (int i = 0; i < N; i++) {
        dist[i][i] = 0;
        for (int j = 0; j < N; j++) {
            if (maps[i][j] == '1') dist[i][j] = getDist(points[i], points[j]);
        }
    }
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j || dist[i][j] >= DOUBLE_MAX) continue;
            path[i] = max(path[i], dist[i][j]);
        }
    }
}

int main(int argc, const char * argv[]) {
    ifstream fin ("cowtour.in");
    ofstream fout ("cowtour.out");
    int N, x, y;
    fin >> N;
    vector<pair<int, int> > points;
    for (int i = 0; i < N; i++) {
        fin >> x >> y;
        points.push_back(make_pair(x, y));
    }
    string line;
    vector<string> maps;
    for (int i = 0; i < N; i++) {
        fin >> line;
        maps.push_back(line);
    }
    vector<int> pre(N, 0);
    for (int i = 0; i < N; i++) {
        pre[i] = i;
    }
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (maps[i][j] == '1') stunion(pre, i, j);
        }
    }
    vector<double> dist(N, 0);
    floyd(maps, points, dist);
    double ans = DOUBLE_MAX;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (stfind(pre, i) != stfind(pre, j)) {
                ans = min(ans, dist[i] + dist[j] + getDist(points[i], points[j]));
            }
        }
    }
    for (int i = 0; i < N; i++) {
        ans = max(ans, dist[i]);
    }
    fout.setf(ios::fixed);
    fout << setprecision(6) << ans << endl;
    return 0;
}
