/*
 ID: cloudzf2
 PROG: stall4
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

int matching(vector<vector<bool> > &maps, vector<int> &link, vector<int> &visited, int N, int M, int cur) {
    for (int i = 0; i < M; i++) {
        if (!visited[i] && maps[cur][i]) {
            visited[i] = true;
            if (link[i] == -1 || matching(maps, link, visited, N, M, link[i])) {
                link[i] = cur;
                return 1;
            }
        }
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("stall4.in");
    ofstream fout ("stall4.out");
    int N, M, ncows, id;
    fin >> N >> M;
    vector<vector<bool> > maps(N, vector<bool>(M, false));
    for (int i = 0; i < N; i++) {
        fin >> ncows;
        for (int j = 0; j < ncows; j++) {
            fin >> id;
            maps[i][id - 1] = true;
        }
    }
    vector<int> link(M, -1);
    vector<int> visited(M, false);
    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) visited[j] = false;
        ans += matching(maps, link, visited, N, M, i);
    }
    fout << ans << endl;
    return 0;
}
