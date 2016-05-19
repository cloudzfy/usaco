/*
 ID: cloudzf2
 PROG: race3
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

bool dfs1(vector<vector<int> > &graph, int removed, int s, int t) {
    vector<bool> visited(graph.size(), false);
    visited[removed] = true;
    stack<int> ss;
    ss.push(s);
    while (!ss.empty()) {
        int u = ss.top();
        ss.pop();
        visited[u] = true;
        for (int i = 0; i < graph[u].size(); i++) {
            if (!visited[graph[u][i]]) {
                if (graph[u][i] == t) return true;
                ss.push(graph[u][i]);
            }
        }
    }
    return false;
}

bool dfs2(vector<vector<int> > &graph, int tested, int s) {
    vector<int> visited(graph.size(), 0);
    stack<int> ss;
    ss.push(s);
    while (!ss.empty()) {
        int u = ss.top();
        ss.pop();
        if (u == tested) continue;
        visited[u] = 2;
        for (int i = 0; i < graph[u].size(); i++) {
            if (!visited[graph[u][i]]) {
                ss.push(graph[u][i]);
            }
        }
    }
    ss.push(tested);
    while (!ss.empty()) {
        int u = ss.top();
        ss.pop();
        visited[u] = 1;
        for (int i = 0; i < graph[u].size(); i++) {
            if (!visited[graph[u][i]]) {
                ss.push(graph[u][i]);
            } else if (visited[graph[u][i]] == 2) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("race3.in");
    ofstream fout ("race3.out");
    vector<vector<int> > graph;
    vector<int> tmp;
    int p;
    while (true) {
        fin >> p;
        if (p >= 0) tmp.push_back(p);
        else if (p == -2) {
            graph.push_back(tmp);
            tmp.clear();
        } else break;
    }
    int N = (int)graph.size();
    vector<int> ans1;
    for (int i = 1; i < N - 1; i++) {
        if (!dfs1(graph, i, 0, N - 1)) {
            ans1.push_back(i);
        }
    }
    vector<int> ans2;
    for (int i = 0; i < ans1.size(); i++) {
        if (!dfs2(graph, ans1[i], 0)) {
            ans2.push_back(ans1[i]);
        }
    }
    fout << ans1.size();
    for (int i = 0; i < ans1.size(); i++) {
        fout << " " << ans1[i];
    }
    fout << endl;
    fout << ans2.size();
    for (int i = 0; i < ans2.size(); i++) {
        fout << " " << ans2[i];
    }
    fout << endl;
    return 0;
}
