/*
 ID: cloudzf2
 PROG: subset
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
    ifstream fin ("subset.in");
    ofstream fout ("subset.out");
    int N;
    fin >> N;
    int sum = N * (1 + N) / 2;
    if (sum % 2 == 1) {
        fout << 0 << endl;
        return 0;
    }
    int M = sum / 2 + 1;
    vector<long long> dp(M, 0);
    dp[0] = 1;
    for (int i = 1; i <= N; i++) {
        for (int j = M - 1; j >= 0; j--) {
            if (dp[j] > 0 && j + i < M) dp[j + i] += dp[j];
        }
    }
    fout << dp[M - 1] / 2 << endl;
    return 0;
}
