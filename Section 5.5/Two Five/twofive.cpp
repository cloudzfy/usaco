/*
 ID: cloudzf2
 PROG: twofive
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

#define INF 2147483647

int dp[6][6][6][6][6];

int dfs(vector<int> &idx, string &W, int depth) {
    if (dp[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]]) {
        return dp[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]];
    }
    int count = 0;
    for (int i = 0; i < 5; i++) {
        if (idx[i] < 5 && (i == 0 || idx[i] < idx[i - 1])) {
            if (W[i * 5 + idx[i]] == 0 || W[i * 5 + idx[i]] == 'A' + depth) {
                idx[i]++;
                count += dfs(idx, W, depth + 1);
                idx[i]--;
            }
            if (W[i * 5 + idx[i]] == 'A' + depth) break;
        }
    }
    dp[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]] = count;
    return count;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("twofive.in");
    ofstream fout ("twofive.out");
    char op;
    fin >> op;
    if (op == 'N') {
        int N;
        fin >> N;
        string W(25, 0);
        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 25; j++) {
                W[i] = 'A' + j;
                vector<int> idx(5, 0);
                memset(dp, 0, sizeof(dp));
                dp[5][5][5][5][5] = 1;
                int count = dfs(idx, W, 0);
                if (N > count) N -= count;
                else break;
            }
        }
        fout << W << endl;
    } else {
        string W;
        fin >> W;
        string tmp(26, 0);
        int N = 0;
        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < W[i] - 'A'; j++) {
                tmp[i] = 'A' + j;
                vector<int> idx(5, 0);
                memset(dp, 0, sizeof(dp));
                dp[5][5][5][5][5] = 1;
                N += dfs(idx, tmp, 0);
            }
            tmp[i] = W[i];
        }
        fout << N + 1 << endl;
    }
    return 0;
}
