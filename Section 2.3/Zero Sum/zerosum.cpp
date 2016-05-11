/*
 ID: cloudzf2
 PROG: zerosum
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

#define sign(x) (x >= 0 ? 1 : -1)

void dfs(int cur, int N, long long term, long long expr, string myans, vector<string> &ans) {
    if (cur == N + 1) {
        if (expr + term == 0) {
            ans.push_back(myans);
        }
        return;
    }
    dfs(cur + 1, N, term * 10 + cur * sign(term), expr, myans + " " + to_string(cur), ans);
    dfs(cur + 1, N, cur, expr + term, myans + "+" + to_string(cur), ans);
    dfs(cur + 1, N, -cur, expr + term, myans + "-" + to_string(cur), ans);
}

int main(int argc, const char * argv[]) {
    ifstream fin ("zerosum.in");
    ofstream fout ("zerosum.out");
    int N;
    fin >> N;
    vector<string> ans;
    dfs(2, N, 1, 0, "1", ans);
    for (int i = 0; i < ans.size(); i++) {
        fout << ans[i] << endl;
    }
    return 0;
}
