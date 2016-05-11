/*
 ID: cloudzf2
 PROG: money
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
    ifstream fin ("money.in");
    ofstream fout ("money.out");
    int V, N, coin;
    fin >> V >> N;
    vector<long long> dp(N + 1, 0);
    dp[0] = 1;
    for (int i = 0; i < V; i++) {
        fin >> coin;
        for (int j = 0; j + coin <= N; j++) {
            dp[j + coin] += dp[j];
        }
    }
    fout << dp[N] << endl;
    return 0;
}
