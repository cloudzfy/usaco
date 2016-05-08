/*
 ID: cloudzf2
 PROG: wormhole
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

using namespace std;

bool checkCycle(vector<int> &pairs, vector<int> &next, int N) {
    for (int i = 0; i < N; i++) {
        int pos = i;
        for (int j = 0; j < N && pos != -1; j++) {
            pos = next[pairs[pos]];
        }
        if (pos != -1) return true;
    }
    return false;
}

int solve(vector<int> &pairs, vector<int> &next, int N) {
    int ans = 0;
    int i = 0;
    while (i < N && pairs[i] != -1) i++;
    if (i == N) {
        if (checkCycle(pairs, next, N)) ans++;
        return ans;
    }
    for (int j = i + 1; j < N; j++) {
        if (pairs[j] == -1) {
            pairs[i] = j;
            pairs[j] = i;
            ans += solve(pairs, next, N);
            pairs[i] = -1;
            pairs[j] = -1;
        }
    }
    return ans;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("wormhole.in");
    ofstream fout ("wormhole.out");
    int N, x, y;
    fin >> N;
    vector<pair<int, int> > coord;
    for (int i = 0; i < N; i++) {
        fin >> x >> y;
        coord.push_back(make_pair(x, y));
    }
    vector<int> pairs(N, -1);
    vector<int> next(N, -1);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (coord[i].second == coord[j].second && coord[i].first < coord[j].first) {
                if (next[i] == -1 || coord[next[i]].first > coord[j].first) {
                    next[i] = j;
                }
            }
        }
    }
    fout << solve(pairs, next, N) << endl;
    return 0;
}
