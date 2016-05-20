/*
 ID: cloudzf2
 PROG: frameup
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

int N, M;

void check(vector<string> &maps, vector<int> &indegree, vector<vector<bool> > &graph, unordered_map<char, int> &m, char cur) {
    int left = M - 1, right = 0, top = N - 1, bottom = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (maps[i][j] == cur) {
                left = min(left, j);
                right = max(right, j);
                top = min(top, i);
                bottom = max(bottom, i);
            }
        }
    }
    for (int i = left; i <= right; i++) {
        if (maps[top][i] != '.' && maps[top][i] != cur) {
            int a = m[cur], b = m[maps[top][i]];
            if (!graph[a][b]) {
                graph[a][b] = true;
                indegree[b]++;
            }
        }
        if (maps[bottom][i] != '.' && maps[bottom][i] != cur) {
            int a = m[cur], b = m[maps[bottom][i]];
            if (!graph[a][b]) {
                graph[a][b] = true;
                indegree[b]++;
            }
        }
    }
    for (int i = top; i <= bottom; i++) {
        if (maps[i][left] != '.' && maps[i][left] != cur) {
            int a = m[cur], b = m[maps[i][left]];
            if (!graph[a][b]) {
                graph[a][b] = true;
                indegree[b]++;
            }
        }
        if (maps[i][right] != '.' && maps[i][right] != cur) {
            int a = m[cur], b = m[maps[i][right]];
            if (!graph[a][b]) {
                graph[a][b] = true;
                indegree[b]++;
            }
        }
    }
}

void dfs(vector<vector<bool> > &graph, vector<int> &indegree, vector<string> &ans, string myans, vector<char> &m, int N) {
    if (myans.length() == N) {
        ans.push_back(myans);
        return;
    }
    for (int i = 0; i < N; i++) {
        if (indegree[i] == 0) {
            indegree[i]--;
            string tmp = myans;
            tmp.push_back(m[i]);
            for (int j = 0; j < N; j++) {
                if (graph[i][j]) indegree[j]--;
            }
            dfs(graph, indegree, ans, tmp, m, N);
            for (int j = 0; j < N; j++) {
                if (graph[i][j]) indegree[j]++;
            }
            indegree[i]++;
        }
    }
}

int main(int argc, const char * argv[]) {
    ifstream fin ("frameup.in");
    ofstream fout ("frameup.out");
    fin >> N >> M;
    vector<string> maps(N, string());
    unordered_map<char, int> m;
    vector<char> mm;
    int count = 0;
    for (int i = 0; i < N; i++) {
        fin >> maps[i];
        for (int j = 0; j < M; j++) {
            if (maps[i][j] != '.') {
                if (m.find(maps[i][j]) == m.end()) {
                    m[maps[i][j]] = count++;
                    mm.push_back(maps[i][j]);
                }
            }
        }
    }
    vector<int> indegree(count, 0);
    vector<vector<bool> > graph(count, vector<bool>(count, false));
    for (auto it = m.begin(); it != m.end(); it++) {
        check(maps, indegree, graph, m, it->first);
    }
    vector<string> ans;
    dfs(graph, indegree, ans, "", mm, count);
    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) {
        fout << ans[i] << endl;
    }
    return 0;
}
