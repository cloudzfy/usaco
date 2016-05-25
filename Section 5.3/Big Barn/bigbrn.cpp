/*
 ID: cloudzf2
 PROG: bigbrn
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

int main(int argc, const char * argv[]) {
    ifstream fin ("bigbrn.in");
    ofstream fout ("bigbrn.out");
    int N, T, x, y;
    fin >> N >> T;
    vector<vector<char> > maps(N, vector<char>(N, '.'));
    vector<vector<int> > dp(N, vector<int>(N, 1));
    for (int i = 0; i < T; i++) {
        fin >> x >> y;
        maps[x - 1][y - 1] = '#';
        dp[x - 1][y - 1] = 0;
    }
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            if (dp[i][j]) dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
        }
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ans = max(ans, dp[i][j]);
        }
    }
    fout << ans << endl;
    return 0;
}
