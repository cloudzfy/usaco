/*
 ID: cloudzf2
 PROG: game1
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
    ifstream fin ("game1.in");
    ofstream fout ("game1.out");
    int N;
    fin >> N;
    vector<int> data(N, 0);
    for (int i = 0; i < N; i++) {
        fin >> data[i];
    }
    vector<vector<pair<int, int> > > dp(N, vector<pair<int, int> >(N, pair<int, int>()));
    for (int i = 0; i < N; i++) {
        if (N % 2 == 0) {
            dp[i][i].first = 0;
            dp[i][i].second = data[i];
        } else {
            dp[i][i].first = data[i];
            dp[i][i].second = 0;
        }
    }
    for (int i = 1; i < N; i++) {
        for (int j = 0; i + j < N; j++) {
            if (i % 2 != N % 2) {
                if (dp[j][j + i - 1].first + data[j + i] > dp[j + 1][j + i].first + data[j]) {
                    dp[j][j + i].first = dp[j][j + i - 1].first + data[j + i];
                    dp[j][j + i].second = dp[j][j + i - 1].second;
                } else {
                    dp[j][j + i].first = dp[j + 1][j + i].first + data[j];
                    dp[j][j + i].second = dp[j + 1][j + i].second;
                }
            } else {
                if (dp[j][j + i - 1].second + data[j + i] > dp[j + 1][j + i].second + data[j]) {
                    dp[j][j + i].first = dp[j][j + i - 1].first;
                    dp[j][j + i].second = dp[j][j + i - 1].second + data[j + i];
                } else {
                    dp[j][j + i].first = dp[j + 1][j + i].first;
                    dp[j][j + i].second = dp[j + 1][j + i].second + data[j];
                }
            }
        }
    }
    fout << dp[0][N - 1].first << " " << dp[0][N - 1].second << endl;
    return 0;
}
