/*
 ID: cloudzf2
 PROG: stamps
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
    ifstream fin ("stamps.in");
    ofstream fout ("stamps.out");
    int K, N;
    fin >> K >> N;
    vector<int> stamps(N, 0);
    int maxStamp = 0;
    for (int i = 0; i < N; i++) {
        fin >> stamps[i];
        maxStamp = max(maxStamp, stamps[i]);
    }
    int M = maxStamp * K;
    vector<int> dp(M + 1, K + 1);
    dp[0] = 0;
    for (int i = 0; i < N; i++) {
        for (int j = stamps[i]; j <= M; j++) {
            if (dp[j - stamps[i]] >= K) continue;
            dp[j] = min(dp[j - stamps[i]] + 1, dp[j]);
        }
    }
    for (int i = 0; i <= M; i++) {
        if (dp[i] > K) {
            fout << i - 1 << endl;
            return 0;
        }
    }
    fout << M << endl;
    return 0;
}
