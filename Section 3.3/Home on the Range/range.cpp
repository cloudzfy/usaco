/*
 ID: cloudzf2
 PROG: range
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

int main(int argc, const char * argv[]) {
    ifstream fin ("range.in");
    ofstream fout ("range.out");
    int N;
    fin >> N;
    vector<string> data(N, string());
    for (int i = 0; i < N; i++) {
        fin >> data[i];
    }
    vector<vector<int> > dp(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        if (data[i][0] == '1') dp[i][0] = 1;
        if (data[0][i] == '1') dp[0][i] = 1;
    }
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            if (data[i][j] == '1') {
                dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
            }
        }
    }
    vector<int> ans(N + 1, 0);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 2; k <= dp[i][j]; k++) {
                ans[k]++;
            }
        }
    }
    for (int i = 2; i <= N; i++) {
        if (ans[i] != 0) fout << i << " " << ans[i] << endl;
    }
    return 0;
}
