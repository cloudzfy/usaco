/*
 ID: cloudzf2
 PROG: concom
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

int main(int argc, const char * argv[]) {
    ifstream fin ("concom.in");
    ofstream fout ("concom.out");
    int n, a, b, p;
    fin >> n;
    int N = 100;
    vector<vector<int> > maps(N, vector<int>(N, 0));
    for (int i = 0; i < n; i++) {
        fin >> a >> b >> p;
        maps[a - 1][b - 1] = p;
    }
    set<pair<int, int> > ans;
    for (int i = 0; i < N; i++) {
        vector<int> stock(N, 0);
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            if (cur != i) ans.insert(make_pair(i + 1, cur + 1));
            for (int j = 0; j < N; j++) {
                if (stock[j] <= 50 && stock[j] + maps[cur][j] > 50) q.push(j);
                stock[j] += maps[cur][j];
            }
        }
    }
    for (auto it = ans.begin(); it != ans.end(); it++) {
        fout << it->first << " " << it->second << endl;
    }
    return 0;
}
