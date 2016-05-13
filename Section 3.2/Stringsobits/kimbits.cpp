/*
 ID: cloudzf2
 PROG: kimbits
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

int main(int argc, const char * argv[]) {
    ifstream fin ("kimbits.in");
    ofstream fout ("kimbits.out");
    int N, L;
    long long I;
    fin >> N >> L >> I;
    vector<vector<long long> > dp(N + 1, vector<long long>(L + 1, 0));
    for (int i = 0; i <= N; i++) {
        dp[i][0] = 1;
    }
    for (int i = 1; i <= L; i++) {
        dp[0][i] = 1;
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= L; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
        }
    }
    string ans(N, '0');
    for (int i = N; i > 0 && L > 0 && I > 0; i--) {
        if (dp[i - 1][L] < I) {
            ans[N - i] = '1';
            I -= dp[i - 1][L];
            L--;
        }
    }
    fout << ans << endl;
    return 0;
}
