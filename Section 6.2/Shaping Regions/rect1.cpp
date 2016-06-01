/*
 ID: cloudzf2
 PROG: rect1
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

struct rect {
    int x1, y1, x2, y2, c;
    rect(int x1, int y1, int x2, int y2, int c) : x1(x1), y1(y1), x2(x2), y2(y2), c(c) {}
};

void addRect(int x1, int y1, int x2, int y2, int c, int idx, int N, map<int, int> &m, vector<rect> &rects) {
    while (idx <= N && (x1 >= rects[idx].x2 || x2 <= rects[idx].x1 || y1 >= rects[idx].y2 || y2 <= rects[idx].y1)) idx++;
    if (idx == N + 1) m[c] += (x2 - x1) * (y2 - y1);
    else {
        if (x1 < rects[idx].x1) {
            addRect(x1, y1, rects[idx].x1, y2, c, idx + 1, N, m, rects);
            x1 = rects[idx].x1;
        }
        if (x2 > rects[idx].x2) {
            addRect(rects[idx].x2, y1, x2, y2, c, idx + 1, N, m, rects);
            x2 = rects[idx].x2;
        }
        if (y1 < rects[idx].y1) {
            addRect(x1, y1, x2, rects[idx].y1, c, idx + 1, N, m, rects);
            y1 = rects[idx].y1;
        }
        if (y2 > rects[idx].y2) {
            addRect(x1, rects[idx].y2, x2, y2, c, idx + 1, N, m, rects);
            y2 = rects[idx].y2;
        }
    }
}

int main(int argc, const char * argv[]) {
    ifstream fin ("rect1.in");
    ofstream fout ("rect1.out");
    int A, B, N;
    int x1, y1, x2, y2, c;
    fin >> A >> B >> N;
    vector<rect> rects;
    map<int, int> m;
    rects.push_back(rect(0, 0, A, B, 1));
    for (int i = 0; i < N; i++) {
        fin >> x1 >> y1 >> x2 >> y2 >> c;
        rects.push_back(rect(x1, y1, x2, y2, c));
    }
    for (int i = N; i >= 0; i--) {
        addRect(rects[i].x1, rects[i].y1, rects[i].x2, rects[i].y2, rects[i].c, i + 1, N, m, rects);
    }
    for (auto it = m.begin(); it != m.end(); it++) {
        fout << it->first << " " << it->second << endl;
    }
    return 0;
}
