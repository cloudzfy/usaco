/*
 ID: cloudzf2
 PROG: runround
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

bool isRunaround(int num) {
    string s = to_string(num);
    vector<int> digits(10, 0);
    int len = (int)s.length();
    for (int i = 0; i < len; i++) {
        if (s[i] == '0') return false;
        digits[s[i] - '0']++;
        if (digits[s[i] - '0'] > 1) return false;
    }
    vector<bool> visited(len, false);
    int idx = 0;
    int count = 0;
    while (!visited[idx]) {
        visited[idx] = true;
        count++;
        idx = (idx + s[idx] - '0') % len;
    }
    return count == len && idx == 0;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("runround.in");
    ofstream fout ("runround.out");
    int M;
    fin >> M;
    while (true) {
        M++;
        if (isRunaround(M)) break;
    }
    fout << M << endl;
    return 0;
}
