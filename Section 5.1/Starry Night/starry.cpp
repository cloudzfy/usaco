/*
 ID: cloudzf2
 PROG: starry
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

using namespace std;

struct node {
    int id;
    vector<pair<int, int> > points;
    node(int id) : id(id) {}
};

void initializeUF(vector<int> &pre) {
    for (int i = 0; i < pre.size(); i++) {
        pre[i] = i;
    }
}

int findUF(vector<int> &pre, int x) {
    if (pre[x] != x) {
        pre[x] = findUF(pre, pre[x]);
    }
    return pre[x];
}

void unionUF(vector<int> &pre, int x, int y) {
    x = findUF(pre, x);
    y = findUF(pre, y);
    pre[y] = x;
}

bool cmp(pair<int, int> &a, pair<int, int> &b) {
    if (a.first == b.first) return a.second < b.second;
    return a.first < b.first;
}

bool orientation(vector<pair<int, int> > &a, vector<pair<int, int> > b, int N) {
    for (int t = 0; t < 4; t++) {
        sort(a.begin(), a.end(), cmp);
        sort(b.begin(), b.end(), cmp);
        int dx = a[0].first - b[0].first;
        int dy = a[0].second - b[0].second;
        bool isValid = true;
        for (int i = 1; i < a.size(); i++) {
            if (b[i].first + dx != a[i].first || b[i].second + dy != a[i].second) {
                isValid = false;
                break;
            }
        }
        if (isValid) return true;
        for (int i = 0; i < b.size(); i++) {
            swap(b[i].first, b[i].second);
            b[i].second = N - b[i].second;
        }
    }
    return false;
}

bool check(vector<pair<int, int> > a, vector<pair<int, int> > b, int N) {
    if (a.size() != b.size()) return false;
    if (orientation(a, b, N)) return true;
    for (int i = 0; i < b.size(); i++) {
        b[i].second = N - b[i].second;
    }
    return orientation(a, b, N);
}

int main(int argc, const char * argv[]) {
    ifstream fin ("starry.in");
    ofstream fout ("starry.out");
    int W, H;
    fin >> W >> H;
    vector<string> maps(H, string());
    for (int i = 0; i < H; i++) {
        fin >> maps[i];
    }
    vector<int> pre(W * H, 0);
    initializeUF(pre);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (maps[i][j] == '1') {
                if (i - 1 >= 0 && maps[i - 1][j] == '1') {
                    unionUF(pre, (i - 1) * W + j, i * W + j);
                }
                if (j - 1 >= 0 && maps[i][j - 1] == '1') {
                    unionUF(pre, i * W + j - 1, i * W + j);
                }
                if (i - 1 >= 0 && j - 1 >= 0 && maps[i - 1][j - 1] == '1') {
                    unionUF(pre, (i - 1) * W + j - 1, i * W + j);
                }
                if (i - 1 >= 0 && j + 1 < W && maps[i - 1][j + 1] == '1') {
                    unionUF(pre, (i - 1) * W + j + 1, i * W + j);
                }
            }
        }
    }
    map<int, int> m;
    vector<node> graph;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (maps[i][j] == '1') {
                int idx = findUF(pre, i * W + j);
                if (m.find(idx) == m.end()) {
                    m[idx] = (int)graph.size();
                    graph.push_back(node(m[idx]));
                }
                graph[m[idx]].points.push_back(make_pair(i, j));
            }
        }
    }
    int count = 0;
    for (int i = 0; i < graph.size(); i++) {
        if (graph[i].id != i) continue;
        graph[i].id = count;
        for (int j = i + 1; j < graph.size(); j++) {
            if (graph[j].id != j) continue;
            if (check(graph[i].points, graph[j].points, max(W, H))) {
                graph[j].id = count;
            }
        }
        count++;
    }
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[i].points.size(); j++) {
            maps[graph[i].points[j].first][graph[i].points[j].second] = graph[i].id + 'a';
        }
    }
    for (int i = 0; i < H; i++) {
        fout << maps[i] << endl;
    }
    return 0;
}
