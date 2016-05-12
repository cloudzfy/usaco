/*
 ID: cloudzf2
 PROG: inflate
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
    ifstream fin ("inflate.in");
    ofstream fout ("inflate.out");
    int M, N, points, minutes;
    fin >> M >> N;
    vector<int> dp(M + 1, 0);
    for (int i = 0; i < N; i++) {
        fin >> points >> minutes;
        for (int j = minutes; j <= M; j++) {
            dp[j] = max(dp[j - minutes] + points, dp[j]);
        }
    }
    fout << dp[M] << endl;
    return 0;
}
