/*
 ID: cloudzf2
 PROG: calfflac
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

int main(int argc, const char * argv[]) {
    ifstream fin ("calfflac.in");
    ofstream fout ("calfflac.out");
    string s, S;
    while (getline(fin, s)) {
        S += s + "\n";
    }
    string newstr = "#";
    vector<int> idx;
    for (int i = 0; i < S.length(); i++) {
        if (S[i] <= 'Z' && S[i] >= 'A') {
            newstr.push_back(S[i] - 'A' + 'a');
            newstr.push_back('#');
            idx.push_back(i);
        } else if (S[i] <= 'z' && S[i] >= 'a') {
            newstr.push_back(S[i]);
            newstr.push_back('#');
            idx.push_back(i);
        }
    }
    vector<int> dp(newstr.length(), 0);
    int C = 0, R = 0;
    for (int i = 1; i < newstr.length(); i++) {
        int j = 2 * C - i;
        dp[i] = R > i ? min(R - i, dp[j]) : 0;
        while (i - 1 - dp[i] >= 0 && i + 1 + dp[i] < newstr.length() && newstr[i - 1 - dp[i]] == newstr[i + 1 + dp[i]]) dp[i]++;
        if (R < i + dp[i]) {
            R = i + dp[i];
            C = i;
        }
    }
    int len = 0, index = -1;
    for (int i = 0; i < newstr.length(); i++) {
        if (dp[i] > len) {
            len = dp[i];
            index = i;
        }
    }
    int a = idx[(index - dp[index]) / 2];
    int b = idx[(index + dp[index]) / 2 - 1];
    fout << len << endl;
    fout << S.substr(a, b - a + 1) << endl;
    return 0;
}
