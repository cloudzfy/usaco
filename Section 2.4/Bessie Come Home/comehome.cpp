/*
 ID: cloudzf2
 PROG: comehome
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

using namespace std;

#define INT_MAX 2147483647

void dijkstra(vector<vector<int> > &maps, vector<int> &dist, int cur, int N) {
    vector<bool> visited(N, false);
    dist[cur] = 0;
    while (true) {
        visited[cur] = true;
        for (int i = 0; i < N; i++) {
            if (maps[cur][i] == INT_MAX) continue;
            dist[i] = min(dist[i], dist[cur] + maps[cur][i]);
        }
        int minDist = INT_MAX;
        int idx = -1;
        for (int i = 0; i < N; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                idx = i;
            }
        }
        if (idx == -1) break;
        cur = idx;
    }
}

int main(int argc, const char * argv[]) {
    ifstream fin ("comehome.in");
    ofstream fout ("comehome.out");
    int P;
    fin >> P;
    string s, t;
    int a, b, d;
    int N = 52;
    vector<vector<int> > maps(N, vector<int>(N, INT_MAX));
    for (int i = 0; i < P; i++) {
        fin >> s >> t >> d;
        if (s[0] <= 'z' && s[0] >= 'a') a = s[0] - 'a';
        else a = s[0] - 'A' + 26;
        if (t[0] <= 'z' && t[0] >= 'a') b = t[0] - 'a';
        else b = t[0] - 'A' + 26;
        maps[a][b] = min(maps[a][b], d);
        maps[b][a] = min(maps[b][a], d);
    }
    vector<int> dist(N, INT_MAX);
    dijkstra(maps, dist, N - 1, N);
    int ans = INT_MAX;
    char idx = 0;
    for (int i = N / 2; i < N - 1; i++) {
        if (ans > dist[i]) {
            ans = dist[i];
            idx = i - N / 2 + 'A';
        }
    }
    fout << idx << " " << ans << endl;
    return 0;
}
