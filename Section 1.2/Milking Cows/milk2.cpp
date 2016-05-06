/*
 ID: cloudzf2
 PROG: milk2
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

using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) return a.second < b.second;
    return a.first < b.first;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("milk2.in");
    ofstream fout ("milk2.out");
    int N, start, end;
    fin >> N;
    vector<pair<int, int> > m;
    for (int i = 0; i < N; i++) {
        fin >> start >> end;
        m.push_back(make_pair(start, end));
    }
    sort(m.begin(), m.end(), cmp);
    start = m[0].first;
    end = m[0].second;
    int continuous = 0, idle = 0;
    for (int i = 1; i < N; i++) {
        if (m[i].first > end) {
            continuous = max(continuous, end - start);
            idle = max(idle, m[i].first - end);
            start = m[i].first;
            end = m[i].second;
        } else if (m[i].second > end) {
            end = m[i].second;
        }
    }
    continuous = max(continuous, end - start);
    fout << continuous << " " << idle << endl;
    return 0;
}
