/*
 ID: cloudzf2
 PROG: msquare
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

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream fin ("msquare.in");
    ofstream fout ("msquare.out");
    int transform[3][8] = {{4, 5, 6, 7, 0, 1, 2, 3}, {3, 0, 1, 2, 7, 4, 5, 6}, {0, 5, 1, 3, 4, 6, 2, 7}};
    unordered_map<string, string> m;
    string s = "12348765";
    queue<pair<string, string> > q;
    q.push(make_pair(s, ""));
    m[s] = "";
    while (!q.empty()) {
        string cur = q.front().first;
        string trans = q.front().second;
        q.pop();
        for (int i = 0; i < 3; i++) {
            char ch = 'A' + i;
            string tmp(8, '0');
            for (int j = 0; j < 8; j++) {
                tmp[j] = cur[transform[i][j]];
            }
            if (m.find(tmp) == m.end()) {
                m[tmp] = trans + ch;
                q.push(make_pair(tmp, trans + ch));
            }
        }
    }
    int idx[8] = {0, 1, 2, 3, 7, 6, 5, 4};
    int num;
    for (int i = 0; i < 8; i++) {
        fin >> num;
        s[idx[i]] = num + '0';
    }
    string trans = m[s];
    fout << trans.length() << endl;
    if (trans.length() == 0) fout << endl;
    for (int i = 0; i < trans.length(); i += 60) {
        fout << trans.substr(i, 60) << endl;
    }
    return 0;
}
