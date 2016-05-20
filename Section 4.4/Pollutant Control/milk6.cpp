/*
 ID: cloudzf2
 PROG: milk6
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

int N, M;
struct node {
    int idx;
    int s, t;
    int c;
    node(int idx, int s, int t, int c) : idx(idx), s(s), t(t), c(c) {}
};

bool bfs(vector<vector<int> > &maps, vector<int> &pre, int s, int t) {
    for (int i = 0; i < N; i++) pre[i] = -1;
    queue<int> q;
    q.push(s);
    pre[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < N; v++) {
            if (maps[u][v] > 0 && pre[v] == -1) {
                pre[v] = u;
                if (v == t) return true;
                q.push(v);
            }
        }
    }
    return false;
}

int EdmondsKarp(vector<vector<int> > maps) {
    int flow = 0;
    int s = 0, t = N - 1;
    vector<int> pre(N, -1);
    while (true) {
        if (!bfs(maps, pre, s, t)) return flow;
        int f = INF;
        for (int u = t; u != s; u = pre[u]) {
            f = min(f, maps[pre[u]][u]);
        }
        flow += f;
        for (int u = t; u != s; u = pre[u]) {
            maps[pre[u]][u] -= f;
            maps[u][pre[u]] += f;
        }
    }
}

bool cmp(node &a, node &b) {
    if (a.c == b.c) return a.idx < b.idx;
    return a.c > b.c;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("milk6.in");
    ofstream fout ("milk6.out");
    int s, t, c;
    fin >> N >> M;
    vector<vector<int> > maps(N, vector<int>(N, 0));
    vector<node> graph;
    for (int i = 0; i < M; i++) {
        fin >> s >> t >> c;
        maps[s - 1][t - 1] += c;
        graph.push_back(node(i + 1, s - 1, t - 1, c));
    }
    int flow = EdmondsKarp(maps);
    fout << flow;
    vector<int> ans;
    sort(graph.begin(), graph.end(), cmp);
    for (int i = 0; i < graph.size(); i++) {
        maps[graph[i].s][graph[i].t] -= graph[i].c;
        int f = EdmondsKarp(maps);
        if (flow - f == graph[i].c) {
            ans.push_back(graph[i].idx);
            flow -= graph[i].c;
            if (flow == 0) break;
        } else {
            maps[graph[i].s][graph[i].t] += graph[i].c;
        }
    }
    sort(ans.begin(), ans.end());
    fout << " " << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        fout << ans[i] << endl;
    }
    return 0;
}
