/*
 ID: cloudzf2
 PROG: schlnet
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

void dfs1(vector<vector<int> > &graph, vector<bool> &visited, int cur, stack<int> &s) {
    visited[cur] = true;
    for (int i = 0; i < graph[cur].size(); i++) {
        if (!visited[graph[cur][i]]) {
            dfs1(graph, visited, graph[cur][i], s);
        }
    }
    s.push(cur);
}

void dfs2(vector<vector<int> > &graph, vector<bool> &visited, int cur, int count, unordered_map<int, int> &m) {
    stack<int> s;
    s.push(cur);
    visited[cur] = true;
    while (!s.empty()) {
        int u = s.top();
        s.pop();
        m[u] = count;
        for (int v = 0; v < graph[u].size(); v++) {
            if (!visited[graph[u][v]]) {
                s.push(graph[u][v]);
                visited[graph[u][v]] = true;
            }
        }
    }
}

void kosaraju(vector<vector<int> > &graph, vector<vector<int> > &invGraph, int N, int &count, unordered_map<int, int> &m) {
    vector<bool> visited(N, false);
    stack<int> s;
    for (int i = 0; i < N; i++) {
        if (!visited[i]) dfs1(graph, visited, i, s);
    }
    for (int i = 0; i < N; i++) visited[i] = false;
    while (!s.empty()) {
        int u = s.top();
        s.pop();
        if (visited[u]) continue;
        dfs2(invGraph, visited, u, count, m);
        count++;
    }
}

int main(int argc, const char * argv[]) {
    ifstream fin ("schlnet.in");
    ofstream fout ("schlnet.out");
    int N, p;
    fin >> N;
    vector<vector<int> > graph(N, vector<int>());
    vector<vector<int> > invGraph(N, vector<int>());
    for (int i = 0; i < N; i++) {
        while (true) {
            fin >> p;
            if (p == 0) break;
            graph[i].push_back(p - 1);
            invGraph[p - 1].push_back(i);
        }
    }
    unordered_map<int, int> m;
    int count = 0;
    kosaraju(graph, invGraph, N, count, m);
    vector<vector<int> > newGraph(count, vector<int>());
    vector<int> indegree(count, 0);
    vector<int> outdegree(count, 0);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < graph[i].size(); j++) {
            if (m[i] == m[graph[i][j]]) continue;
            newGraph[m[i]].push_back(m[graph[i][j]]);
            indegree[m[graph[i][j]]]++;
            outdegree[m[i]]++;
        }
    }
    int ans1 = 0, ans2 = 0;
    for (int i = 0; i < count; i++) {
        if (indegree[i] == 0) ans1++;
        if (outdegree[i] == 0) ans2++;
    }
    fout << ans1 << endl;
    if (count == 1) fout << 0 << endl;
    else fout << max(ans1, ans2) << endl;
    return 0;
}
