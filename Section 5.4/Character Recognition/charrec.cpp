/*
 ID: cloudzf2
 PROG: charrec
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

int getDiff1(vector<vector<int> > &mat, int s1, int s2) {
    int count = 0;
    for (int i = 0; i < 20; i++) {
        count += mat[s2 + i][s1 + i];
    }
    return count;
}

int getDiff2(vector<vector<int> > &mat, int s1, int s2) {
    int count = INF;
    for (int dup = 0; dup < 20; dup++) {
        int k = s2, tmp = 0;
        for (int i = 0; i < 20; i++) {
            if (k == s2 + dup) k++;
            tmp += mat[k][s1 + i];
            k++;
        }
        count = min(count, tmp);
    }
    return count;
}

int getDiff3(vector<vector<int> > &mat, int s1, int s2) {
    int count = INF;
    for (int ign = 0; ign < 20; ign++) {
        int tmp = 0, k = s2;
        for (int i = 0; i < 20; i++) {
            if (i == ign) continue;
            tmp += mat[k][s1 + i];
            k++;
        }
        count = min(count, tmp);
    }
    return count;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("charrec.in");
    ofstream fout ("charrec.out");
    ifstream font ("font.in");
    int NF;
    font >> NF;
    string s;
    vector<string> m(NF, "");
    for (int i = 0; i < NF; i++) {
        font >> m[i];
    }
    string ch = " abcdefghijklmnopqrstuvwxyz";
    int N;
    fin >> N;
    vector<string> data(N, "");
    for (int i = 0; i < N; i++) {
        fin >> data[i];
    }
    vector<vector<int> > mat(N, vector<int>(NF, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < NF; j++) {
            for (int k = 0; k < 20; k++) {
                if (data[i][k] != m[j][k]) mat[i][j]++;
            }
        }
    }
    vector<pair<int, string> > dp(N + 1, make_pair(INF, ""));
    dp[0].first = 0;
    for (int t = 19; t <= N; t++) {
        if (t >= 20 && dp[t - 20].first != INF) {
            int minDiff = INF;
            string minCh;
            for (int i = 0; i < 27; i++) {
                int diff = getDiff1(mat, i * 20, t - 20);
                if (minDiff > diff) {
                    minDiff = diff;
                    minCh = ch[i];
                }
            }
            if (dp[t].first > minDiff + dp[t - 20].first) {
                dp[t].first = minDiff + dp[t - 20].first;
                dp[t].second = dp[t - 20].second + minCh;
            }
        }
        if (t >= 21 && dp[t - 21].first != INF) {
            int minDiff = INF;
            string minCh;
            for (int i = 0; i < 27; i++) {
                int diff = getDiff2(mat, i * 20, t - 21);
                if (minDiff > diff) {
                    minDiff = diff;
                    minCh = ch[i];
                }
            }
            if (dp[t].first > minDiff + dp[t - 21].first) {
                dp[t].first = minDiff + dp[t - 21].first;
                dp[t].second = dp[t - 21].second + minCh;
            }
        }
        if (t >= 19 && dp[t - 19].first != INF) {
            int minDiff = INF;
            string minCh;
            for (int i = 0; i < 27; i++) {
                int diff = getDiff3(mat, i * 20, t - 19);
                if (minDiff > diff) {
                    minDiff = diff;
                    minCh = ch[i];
                }
            }
            if (dp[t].first > minDiff + dp[t - 19].first) {
                dp[t].first = minDiff + dp[t - 19].first;
                dp[t].second = dp[t - 19].second + minCh;
            }
        }
    }
    fout << dp[N].second << endl;
    return 0;
}
