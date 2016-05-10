/*
 ID: cloudzf2
 PROG: lamps
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

void dfs(map<string, vector<int> > &ans, string states, int step, int count) {
    if (step == 1) {
        dfs(ans, states, step + 1, count);
        for (int i = 0; i < states.length(); i++) {
            if (states[i] == '1') states[i] = '0';
            else states[i] = '1';
        }
        dfs(ans, states, step + 1, count + 1);
    } else if (step == 2) {
        dfs(ans, states, step + 1, count);
        for (int i = 0; i < states.length(); i += 2) {
            if (states[i] == '1') states[i] = '0';
            else states[i] = '1';
        }
        dfs(ans, states, step + 1, count + 1);
    } else if (step == 3) {
        dfs(ans, states, step + 1, count);
        for (int i = 1; i < states.length(); i += 2) {
            if (states[i] == '1') states[i] = '0';
            else states[i] = '1';
        }
        dfs(ans, states, step + 1, count + 1);
    } else {
        ans[states].push_back(count);
        for (int i = 0; i < states.length(); i += 3) {
            if (states[i] == '1') states[i] = '0';
            else states[i] = '1';
        }
        ans[states].push_back(count + 1);
    }
}

int main(int argc, const char * argv[]) {
    ifstream fin ("lamps.in");
    ofstream fout ("lamps.out");
    int N, C;
    fin >> N >> C;
    vector<int> on, off;
    int state;
    while (true) {
        fin >> state;
        if (state == -1) break;
        on.push_back(state);
    }
    while (true) {
        fin >> state;
        if (state == -1) break;
        off.push_back(state);
    }
    map<string, vector<int> > ans;
    string states;
    for (int i = 0; i < N; i++) {
        states.push_back('1');
    }
    dfs(ans, states, 1, 0);
    bool hasSol = false;
    for (auto it = ans.begin(); it != ans.end(); it++) {
        vector<int> count = it->second;
        bool pressable = false;
        for (int i = 0; i < count.size(); i++) {
            if (count[i] <= C && (C - count[i]) % 2 == 0) pressable = true;
        }
        if (!pressable) continue;
        string tmp = it->first;
        bool isValid = true;
        for (int i = 0; i < on.size(); i++) {
            if (tmp[on[i] - 1] == '0') {
                isValid = false;
                break;
            }
        }
        if (!isValid) continue;
        for (int i = 0; i < off.size(); i++) {
            if (tmp[off[i] - 1] == '1') {
                isValid = false;
                break;
            }
        }
        if (isValid) {
            fout << tmp << endl;
            hasSol = true;
        }
    }
    if (!hasSol) fout << "IMPOSSIBLE" << endl;
    return 0;
}
