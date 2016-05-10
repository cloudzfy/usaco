/*
 ID: cloudzf2
 PROG: holstein
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

using namespace std;

bool compare(vector<int> &a, vector<int> &b) {
    for (int i = 0; i < a.size(); i++) {
        if (a[i] < b[i]) return true;
    }
    return false;
}
void dfs(vector<int> &vitamins, vector<vector<int> > &scoops, int cur, vector<int> myans, vector<int> &ans) {
    myans.push_back(cur + 1);
    for (int i = 0; i < vitamins.size(); i++) {
        vitamins[i] -= scoops[cur][i];
    }
    bool satisfied = true;
    for (int i = 0; i < vitamins.size(); i++) {
        if (vitamins[i] > 0) {
            satisfied = false;
            break;
        }
    }
    if (satisfied) {
        if (myans.size() < ans.size()) ans = myans;
        else if (myans.size() == ans.size() && compare(myans, ans)) ans = myans;
        return;
    }
    for (int i = cur + 1; i < scoops.size(); i++) {
        vector<int> tmp(vitamins);
        dfs(tmp, scoops, i, myans, ans);
    }
}
int main(int argc, const char * argv[]) {
    ifstream fin ("holstein.in");
    ofstream fout ("holstein.out");
    int V, G;
    fin >> V;
    vector<int> vitamins(V, 0);
    for (int i = 0; i < V; i++) {
        fin >> vitamins[i];
    }
    fin >> G;
    vector<vector<int> > scoops(G, vector<int>(V, 0));
    for (int i = 0; i < G; i++) {
        for (int j = 0; j < V; j++) {
            fin >> scoops[i][j];
        }
    }
    vector<int> ans(V, V);
    vector<int> myans;
    for (int i = 0; i < scoops.size(); i++) {
        vector<int> tmp(vitamins);
        dfs(tmp, scoops, i, myans, ans);
    }
    fout << ans.size();
    for (int i = 0; i < ans.size(); i++) {
        fout << " " << ans[i];
    }
    fout << endl;
    return 0;
}
