/*
 ID: cloudzf2
 PROG: milk
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

using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
    return a.first < b.first;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("milk.in");
    ofstream fout ("milk.out");
    int N, M;
    int P, A;
    vector<pair<int, int> > milk;
    fin >> N >> M;
    for (int i = 0; i < M; i++) {
        fin >> P >> A;
        milk.push_back(make_pair(P, A));
    }
    sort(milk.begin(), milk.end(), cmp);
    int cost = 0;
    for (int i = 0; i < M; i++) {
        cost += milk[i].first * min(N, milk[i].second);
        N -= min(N, milk[i].second);
        if (N == 0) break;
    }
    fout << cost << endl;
    return 0;
}
