/*
 ID: cloudzf2
 PROG: milk4
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

int Q, P;

bool dfsid(vector<int> &pail, vector<int> &ans, int maxNum, int cur) {
    if (maxNum == ans.size()) {
        vector<bool> dp(Q + 1, false);
        dp[0] = true;
        for (int i = 0; i < ans.size(); i++) {
            for (int j = ans[i]; j <= Q; j++) {
                if (dp[j - ans[i]]) dp[j] = true;
            }
        }
        return dp[Q];
    }
    if (cur == pail.size()) return false;
    ans.push_back(pail[cur]);
    if (dfsid(pail, ans, maxNum, cur + 1)) return true;
    ans.pop_back();
    if (dfsid(pail, ans, maxNum, cur + 1)) return true;
    return false;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("milk4.in");
    ofstream fout ("milk4.out");
    fin >> Q >> P;
    vector<int> pail(P, 0);
    for (int i = 0; i < P; i++) {
        fin >> pail[i];
    }
    sort(pail.begin(), pail.end());
    vector<int> ans;
    for (int i = 1; i <= P; i++) {
        if (dfsid(pail, ans, i, 0)) break;
    }
    fout << ans.size();
    for (int i = 0; i < ans.size(); i++) {
        fout << " " << ans[i];
    }
    fout << endl;
    return 0;
}
