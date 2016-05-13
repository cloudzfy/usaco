/*
 ID: cloudzf2
 PROG: butter
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

using namespace std;

#define INT_MAX 2147483647

struct cmp {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
        return a.second > b.second;
    }
};
int dijkstra(vector<vector<pair<int, int> > > &paths, vector<int> & count, int start, int P) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, cmp> pq;
    vector<bool> visited(P, false);
    vector<int> dist(P, INT_MAX);
    pq.push(make_pair(start, 0));
    int cost = 0;
    while (!pq.empty()) {
        int cur = pq.top().first;
        int d = pq.top().second;
        pq.pop();
        if (visited[cur]) continue;
        visited[cur] = true;
        cost += d * count[cur];
        dist[cur] = d;
        for (int i = 0; i < paths[cur].size(); i++) {
            if (visited[paths[cur][i].first]) continue;
            pq.push(make_pair(paths[cur][i].first, d + paths[cur][i].second));
        }
    }
    return cost;
}
int main(int argc, const char * argv[]) {
    ifstream fin ("butter.in");
    ofstream fout ("butter.out");
    int N, P, C, a, b, l;
    fin >> N >> P >> C;
    vector<int> count(P, 0);
    for (int i = 0; i < N; i++) {
        fin >> a;
        count[a - 1]++;
    }
    vector<vector<pair<int, int> > > paths(P, vector<pair<int, int> >());
    for (int i = 0; i < C; i++) {
        fin >> a >> b >> l;
        paths[a - 1].push_back(make_pair(b - 1, l));
        paths[b - 1].push_back(make_pair(a - 1, l));
    }
    int ans = INT_MAX;
    for (int i = 0; i < P; i++) {
        ans = min(ans, dijkstra(paths, count, i, P));
    }
    fout << ans << endl;
    return 0;
}
