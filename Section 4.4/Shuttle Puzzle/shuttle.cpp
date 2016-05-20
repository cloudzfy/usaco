/*
 ID: cloudzf2
 PROG: shuttle
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

int main(int argc, const char * argv[]) {
    ifstream fin ("shuttle.in");
    ofstream fout ("shuttle.out");
    int N;
    fin >> N;
    string s = string(N, 'W') + " " + string(N, 'B');
    string t = string(N, 'B') + " " + string(N, 'W');
    stack<string> q;
    unordered_map<string, string> m;
    q.push(s);
    while (!q.empty()) {
        string u = q.top();
        q.pop();
        if (u == t) break;
        int idx = 0;
        while (u[idx] != ' ') idx++;
        if (idx + 2 < u.length() && u[idx + 2] == 'B') {
            string v = u;
            v[idx] = 'B';
            v[idx + 2] = ' ';
            if (m.find(v) == m.end()) {
                q.push(v);
                m[v] = u;
            }
        }
        if (idx + 1 < u.length() && u[idx + 1] == 'B') {
            string v = u;
            v[idx] = 'B';
            v[idx + 1] = ' ';
            if (m.find(v) == m.end()) {
                q.push(v);
                m[v] = u;
            }
        }
        if (idx - 1 >= 0 && u[idx - 1] == 'W') {
            string v = u;
            v[idx] = 'W';
            v[idx - 1] = ' ';
            if (m.find(v) == m.end()) {
                q.push(v);
                m[v] = u;
            }
        }
        if (idx - 2 >= 0 && u[idx - 2] == 'W') {
            string v = u;
            v[idx] = 'W';
            v[idx - 2] = ' ';
            if (m.find(v) == m.end()) {
                q.push(v);
                m[v] = u;
            }
        }
    }
    stack<int> ans;
    string u = t;
    while (u != s) {
        for (int i = 0; i < u.length(); i++) {
            if (u[i] == ' ') {
                ans.push(i + 1);
                break;
            }
        }
        u = m[u];
    }
    fout << ans.top();
    ans.pop();
    int count = 1;
    while (!ans.empty()) {
        if (count % 20 == 0) fout << endl;
        else fout << " ";
        fout << ans.top();
        ans.pop();
        count++;
    }
    fout << endl;
    return 0;
}
