/*
 ID: cloudzf2
 PROG: fence6
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

#define INF 100000000

struct fence {
    int length;
    unordered_set<int> m1;
    unordered_set<int> m2;
    fence() {}
    fence(int length) : length(length) {}
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

int main(int argc, const char * argv[]) {
    ifstream fin ("fence6.in");
    ofstream fout ("fence6.out");
    int M, M1, M2, s, e, l;
    fin >> M;
    vector<fence> m(M, fence());
    for (int i = 0; i < M; i++) {
        fin >> s >> l >> M1 >> M2;
        fence tmp(l);
        for (int j = 0; j < M1; j++) {
            fin >> e;
            tmp.m1.insert(e - 1);
        }
        for (int j = 0; j < M2; j++) {
            fin >> e;
            tmp.m2.insert(e - 1);
        }
        m[s - 1] = tmp;
    }
    int N = 2 * M;
    vector<int> pre(N, 0);
    initializeUF(pre);
    for (int i = 0; i < M; i++) {
        for (auto it = m[i].m1.begin(); it != m[i].m1.end(); it++) {
            int j = *it;
            if (m[j].m1.find(i) != m[j].m1.end()) unionUF(pre, 2 * i, 2 * j);
            if (m[j].m2.find(i) != m[j].m2.end()) unionUF(pre, 2 * i, 2 * j + 1);
        }
        for (auto it = m[i].m2.begin(); it != m[i].m2.end(); it++) {
            int j = *it;
            if (m[j].m1.find(i) != m[j].m1.end()) unionUF(pre, 2 * i + 1, 2 * j);
            if (m[j].m2.find(i) != m[j].m2.end()) unionUF(pre, 2 * i + 1, 2 * j + 1);
        }
    }
    vector<vector<int> > maps(N, vector<int>(N, INF));
    for (int i = 0; i < M; i++) {
        maps[findUF(pre, 2 * i)][findUF(pre, 2 * i + 1)] = m[i].length;
        maps[findUF(pre, 2 * i + 1)][findUF(pre, 2 * i)] = m[i].length;
    }
    int ans = INF;
    vector<vector<int> > mymaps = maps;
    for (int k = 0; k < N; k++) {
        if (pre[k] != k) continue;
        for (int i = 0; i < k; i++) {
            if (pre[i] != i) continue;
            for (int j = 0; j < i; j++) {
                if (pre[j] != j) continue;
                ans = min(ans, maps[i][j] + mymaps[j][k] + mymaps[k][i]);
            }
        }
        for (int i = 0; i < N; i++) {
            if (pre[i] != i) continue;
            for (int j = 0; j < i; j++) {
                if (pre[j] != j) continue;
                maps[i][j] = min(maps[i][j], maps[i][k] + maps[k][j]);
                maps[j][i] = maps[i][j];
            }
        }
    }
    fout << ans << endl;
    return 0;
}
