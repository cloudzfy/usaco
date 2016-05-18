/*
 ID: cloudzf2
 PROG: ditch
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

#define INF 2147483647

bool bfs(vector<vector<int> > &maps, vector<int> &pre, int s, int t, int N) {
    for (int i = 0; i < N; i++) {
        pre[i] = -1;
    }
    queue<int> q;
    q.push(s);
    pre[s] = 0;
    while (!q.empty()) {
        s = q.front();
        q.pop();
        for (int i = 0; i < N; i++) {
            if (maps[s][i] > 0 && pre[i] == -1) {
                pre[i] = s;
                if (i == t) return true;
                q.push(i);
            }
        }
    }
    return false;
}

int EdmondsKarp(vector<vector<int> > &maps, int s, int t, int N) {
    int ans = 0;
    vector<int> pre(N, 0);
    while (true) {
        if (!bfs(maps, pre, s, t, N)) break;
        int flow = INF;
        for (int i = t; i != s; i = pre[i]) {
            flow = min(flow, maps[pre[i]][i]);
        }
        for (int i = t; i != s; i = pre[i]) {
            maps[pre[i]][i] -= flow;
            maps[i][pre[i]] += flow;
        }
        ans += flow;
    }
    return ans;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("ditch.in");
    ofstream fout ("ditch.out");
    int N, M, S, E, C;
    fin >> M >> N;
    vector<vector<int> > maps(N, vector<int>(N, 0));
    for (int i = 0; i < M; i++) {
        fin >> S >> E >> C;
        maps[S - 1][E - 1] += C;
    }
    fout << EdmondsKarp(maps, 0, N - 1, N) << endl;
    return 0;
}
