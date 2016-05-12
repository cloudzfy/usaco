/*
 ID: cloudzf2
 PROG: agrinet
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

int main(int argc, const char * argv[]) {
    ifstream fin ("agrinet.in");
    ofstream fout ("agrinet.out");
    int N;
    fin >> N;
    vector<vector<int> > maps(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fin >> maps[i][j];
        }
    }
    vector<int> dist(N, INT_MAX);
    vector<bool> visited(N, false);
    int ans = 0;
    int count = 0, cur = 0;
    while (count < N - 1) {
        visited[cur] = true;
        for (int i = 0; i < N; i++) {
            dist[i] = min(dist[i], maps[cur][i]);
        }
        int minDist = INT_MAX;
        for (int i = 0; i < N; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                cur = i;
            }
        }
        ans += minDist;
        count++;
    }
    fout << ans << endl;
    return 0;
}
