/*
 ID: cloudzf2
 PROG: telecow
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

bool bfs(vector<vector<int> > &graph, vector<int> &pre, int s, int t, int N) {
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < N; v++) {
            if (graph[u][v] > 0 && pre[v] == -1) {
                pre[v] = u;
                if (v == t) return true;
                q.push(v);
            }
        }
    }
    return false;
}

int EdmondsKarp(vector<vector<int> > graph, int s, int t, int N) {
    vector<int> pre(N, -1);
    int flow = 0;
    while (true) {
        for (int i = 0; i < N; i++) pre[i] = -1;
        if (bfs(graph, pre, s, t, N)) {
            int f = INF;
            for (int i = t; i != s; i = pre[i]) {
                f = min(f, graph[pre[i]][i]);
            }
            flow += f;
            for (int i = t; i != s; i = pre[i]) {
                graph[pre[i]][i] -= f;
                graph[i][pre[i]] += f;
            }
        } else break;
    }
    return flow;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("telecow.in");
    ofstream fout ("telecow.out");
    int N, M, c1, c2, a, b;
    fin >> N >> M >> c1 >> c2;
    vector<vector<int> > graph(2 * N, vector<int>(2 * N, 0));
    for (int i = 0; i < M; i++) {
        fin >> a >> b;
        graph[2 * (a - 1) + 1][2 * (b - 1)]++;
        graph[2 * (b - 1) + 1][2 * (a - 1)]++;
    }
    for (int i = 0; i < N; i++) {
        graph[2 * i][2 * i + 1]++;
    }
    int s = 2 * (c1 - 1) + 1, t = 2 * (c2 - 1);
    int flow = EdmondsKarp(graph, s, t, 2 * N);
    vector<int> ans;
    for (int i = 0; i < N; i++) {
        if (i == c1 - 1 || i == c2 - 1) continue;
        graph[2 * i][2 * i + 1]--;
        int f = EdmondsKarp(graph, s, t, 2 * N);
        if (flow > f) {
            flow = f;
            ans.push_back(i + 1);
        } else {
            graph[2 * i][2 * i + 1]++;
        }
        if (flow == 0) break;
    }
    fout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        if (i != 0) fout << " ";
        fout << ans[i];
    }
    fout << endl;
    return 0;
}
