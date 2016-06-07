/*
 ID: cloudzf2
 PROG: checker
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

int N;
int full;
vector<vector<int> > ans;

bool dfs1(int col, int ld, int rd, vector<int> &myans) {
    if (col == full) {
        ans.push_back(myans);
        if (ans.size() == 3) return true;
    }
    int allowed = full & (~(col | ld | rd));
    int count = 0;
    while (allowed) {
        int pos = allowed & (~allowed + 1);
        while (!((1 << count) & pos)) count++;
        allowed -= pos;
        myans.push_back(count + 1);
        if (dfs1(col | pos, (ld | pos) >> 1, (rd | pos) << 1, myans)) return true;
        myans.pop_back();
    }
    return false;
}

int dfs2(int col, int ld, int rd) {
    if (col == full) return 1;
    int myans = 0;
    int allowed = full & (~(col | ld | rd));
    while (allowed) {
        int pos = allowed & (~allowed + 1);
        allowed -= pos;
        myans += dfs2(col | pos, (ld | pos) >> 1, (rd | pos) << 1);
    }
    return myans;
}
int main(int argc, const char * argv[]) {
    ifstream fin ("checker.in");
    ofstream fout ("checker.out");
    fin >> N;
    full = (1 << N) - 1;
    vector<int> myans;
    dfs1(0, 0, 0, myans);
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[i].size(); j++) {
            if (j != 0) fout << " ";
            fout << ans[i][j];
        }
        fout << endl;
    }
    fout << dfs2(0, 0, 0) << endl;
    return 0;
}
