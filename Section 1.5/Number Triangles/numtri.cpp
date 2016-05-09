/*
 ID: cloudzf2
 PROG: numtri
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

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream fin ("numtri.in");
    ofstream fout ("numtri.out");
    int N;
    fin >> N;
    vector<vector<int> > tri(N, vector<int>(N, 0));
    vector<vector<int> > dp(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            fin >> tri[i][j];
        }
    }
    dp[0][0] = tri[0][0];
    for (int i = 1; i < N; i++) {
        dp[i][0] = dp[i - 1][0] + tri[i][0];
        for (int j = 1; j < i; j++) {
            dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j]) + tri[i][j];
        }
        dp[i][i] = dp[i - 1][i - 1] + tri[i][i];
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        ans = max(ans, dp[N - 1][i]);
    }
    fout << ans << endl;
    return 0;
}
