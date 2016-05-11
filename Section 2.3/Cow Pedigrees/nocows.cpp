/*
 ID: cloudzf2
 PROG: nocows
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

int main(int argc, const char * argv[]) {
    ifstream fin ("nocows.in");
    ofstream fout ("nocows.out");
    int N, K;
    fin >> N >> K;
    vector<vector<int> > dp(N + 1, vector<int>(K + 1, 0));
    for (int i = 0; i <= K; i++) {
        dp[0][i] = 1;
    }
    for (int i = 1; i <= N; i += 2) {
        for (int j = 1; j <= K; j++) {
            for (int k = 0; k <= i - 1; k++) {
                dp[i][j] = (dp[i][j] + dp[k][j - 1] * dp[i - 1 - k][j - 1]) % 9901;
            }
        }
    }
    fout << (dp[N][K] - dp[N][K - 1] + 9901) % 9901 << endl;
    return 0;
}
