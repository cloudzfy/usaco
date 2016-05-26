/*
 ID: cloudzf2
 PROG: tour
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

int main(int argc, const char * argv[]) {
    ifstream fin ("tour.in");
    ofstream fout ("tour.out");
    int N, V;
    string s;
    fin >> N >> V;
    unordered_map<string, int> cities;
    for (int i = 0; i < N; i++) {
        fin >> s;
        cities[s] = i;
    }
    string a, b;
    vector<vector<bool> > graph(N, vector<bool>(N, false));
    for (int i = 0; i < V; i++) {
        fin >> a >> b;
        graph[cities[a]][cities[b]] = true;
        graph[cities[b]][cities[a]] = true;
    }
    vector<vector<int> > dp(N, vector<int>(N, 0));
    dp[0][0] = 1;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            for (int k = 0; k < j; k++) {
                if (graph[k][j] && dp[i][k] > 0) {
                    dp[i][j] = max(dp[i][j], dp[i][k] + 1);
                    dp[j][i] = dp[i][j];
                }
            }
        }
    }
    int ans = 1;
    for (int i = 0; i < N; i++) {
        if (dp[i][N - 1] > 0 && graph[i][N - 1]) ans = max(ans, dp[i][N - 1]);
    }
    fout << ans << endl;
    return 0;
}
