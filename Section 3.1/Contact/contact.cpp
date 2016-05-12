/*
 ID: cloudzf2
 PROG: contact
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

bool cmp(const string &a, const string &b) {
    if (a.length() == b.length()) return a < b;
    return a.length() < b.length();
}

int main(int argc, const char * argv[]) {
    ifstream fin ("contact.in");
    ofstream fout ("contact.out");
    int A, B, N;
    string s, seq;
    fin >> A >> B >> N;
    while(fin >> seq) {
        s += seq;
    }
    unordered_map<string, int> m;
    for (int i = 0; i < s.length(); i++) {
        for (int j = A; j <= B && i + j - 1 < s.length(); j++) {
            m[s.substr(i, j)]++;
        }
    }
    map<int, vector<string> > ans;
    for (auto it = m.begin(); it != m.end(); it++) {
        ans[it->second].push_back(it->first);
    }
    int count = 0;
    for (auto it = ans.rbegin(); it != ans.rend(); it++) {
        fout << it->first << endl;
        vector<string> strs = it->second;
        sort(strs.begin(), strs.end(), cmp);
        for (int i = 0; i < strs.size(); i++) {
            if (i % 6 == 0) {
                if (i != 0) fout << endl;
            } else fout << " ";
            fout << strs[i];
        }
        fout << endl;
        if (++count == N) break;
    }
    return 0;
}
