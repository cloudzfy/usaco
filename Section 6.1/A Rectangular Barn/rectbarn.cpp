/*
 ID: cloudzf2
 PROG: rectbarn
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
    ifstream fin ("rectbarn.in");
    ofstream fout ("rectbarn.out");
    int R, C, P, x, y;
    fin >> R >> C >> P;
    vector<vector<int> > maps(R, vector<int>());
    for (int i = 0; i < P; i++) {
        fin >> x >> y;
        maps[x - 1].push_back(y - 1);
    }
    int ans = 0;
    stack<pair<int, int> > s;
    vector<int> dp(C + 1, 0);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) dp[j]++;
        for (int j = 0; j < maps[i].size(); j++) dp[maps[i][j]] = 0;
        for (int j = 0; j < C + 1; j++) {
            while (!s.empty() && s.top().second > dp[j]) {
                int height = s.top().second;
                s.pop();
                ans = max(ans, s.empty() ? j * height : (j - s.top().first - 1) * height);
            }
            s.push(make_pair(j, dp[j]));
        }
        while (!s.empty()) s.pop();
    }
    fout << ans << endl;
    return 0;
}
