/*
 ID: cloudzf2
 PROG: window
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

struct windowing {
    int x1, y1;
    int x2, y2;
    int level;
    windowing() {}
    windowing(int x1, int y1, int x2, int y2, int level) : x1(x1), y1(y1), x2(x2), y2(y2), level(level) {}
};

bool cmp(const windowing &a, const windowing &b) {
    return a.level < b.level;
}

int cover(vector<windowing> &data, int x1, int y1, int x2, int y2, int idx) {
    while (idx < (int)data.size() && (x1 >= data[idx].x2 || x2 <= data[idx].x1
        || y1 >= data[idx].y2 || y2 <= data[idx].y1)) {
        idx++;
    }
    if (idx == (int)data.size()) return (x2 - x1) * (y2 - y1);
    int area = 0;
    if (x1 < data[idx].x1) {
        area += cover(data, x1, y1, data[idx].x1, y2, idx);
        x1 = data[idx].x1;
    }
    if (x2 > data[idx].x2) {
        area += cover(data, data[idx].x2, y1, x2, y2, idx);
        x2 = data[idx].x2;
    }
    if (y1 < data[idx].y1) {
        area += cover(data, x1, y1, x2, data[idx].y1, idx);
        y1 = data[idx].y1;
    }
    if (y2 > data[idx].y2) {
        area += cover(data, x1, data[idx].y2, x2, y2, idx);
        y2 = data[idx].y2;
    }
    return area;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("window.in");
    ofstream fout ("window.out");
    char c;
    char op, I;
    int x, y, X, Y;
    unordered_map<char, windowing> m;
    int top = 0, bottom = 0;
    while (fin >> op) {
        if (op == 'w') {
            fin >> c >> I >> c >> x >> c >> y >> c >> X >> c >> Y >> c;
            if (x > X) swap(x, X);
            if (y > Y) swap(y, Y);
            m[I] = windowing(x, y, X, Y, top++);
        } else if (op == 't') {
            fin >> c >> I >> c;
            m[I].level = top++;
        } else if (op == 'b') {
            fin >> c >> I >> c;
            m[I].level = --bottom;
        } else if (op == 'd') {
            fin >> c >> I >> c;
            m.erase(m.find(I));
        } else if (op == 's') {
            fin >> c >> I >> c;
            vector<windowing> data;
            for (auto it = m.begin(); it != m.end(); it++) {
                if (it->second.level > m[I].level) {
                    windowing tmp = it->second;
                    tmp.x1 = max(m[I].x1, tmp.x1);
                    tmp.x2 = min(m[I].x2, tmp.x2);
                    tmp.y1 = max(m[I].y1, tmp.y1);
                    tmp.y2 = min(m[I].y2, tmp.y2);
                    if (tmp.x1 >= tmp.x2 || tmp.y1 >= tmp.y2) continue;
                    data.push_back(tmp);
                }
            }
            sort(data.begin(), data.end(), cmp);
            double area = (m[I].x2 - m[I].x1) * (m[I].y2 - m[I].y1);
            double covered = 0;
            for (int i = (int)data.size() - 1; i >= 0; i--) {
                covered += cover(data, data[i].x1, data[i].y1, data[i].x2, data[i].y2, i + 1);
            }
            fout.setf(ios::fixed);
            fout << setprecision(3) << 100 * (1 - covered / area) << endl;
        }
    }
    return 0;
}
