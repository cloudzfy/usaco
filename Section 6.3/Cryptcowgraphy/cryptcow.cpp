/*
 ID: cloudzf2
 PROG: cryptcow
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
#include <cmath>

using namespace std;

#define INF 2147483647

unordered_set<int> m;

string origin = "Begin the Escape execution at the Break of Dawn";

string decryption(string s, int c, int o, int w) {
    string ans((int)s.length() - 3, 0);
    int idx = 0;
    for (int i = 0; i < c; i++) {
        ans[idx++] = s[i];
    }
    for (int i = o + 1; i < w; i++) {
        ans[idx++] = s[i];
    }
    for (int i = c + 1; i < o; i++) {
        ans[idx++] = s[i];
    }
    for (int i = w + 1; i < s.length(); i++) {
        ans[idx++] = s[i];
    }
    return ans;
}

bool checkFrequency(string &s) {
    int count[128][2];
    memset(count, 0, sizeof(count));
    for (int i = 0; i < origin.length(); i++) {
        count[origin[i]][0]++;
    }
    for (int i = 0; i < s.length(); i++) {
        count[s[i]][1]++;
    }
    for (int i = 0; i < 128; i++) {
        if (i == 'C' || i == 'O' || i == 'W') continue;
        if (count[i][0] != count[i][1]) return false;
    }
    return true;
}

bool checkPrefix(string &s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == 'C') break;
        if (s[i] != origin[i]) return false;
    }
    return true;
}

bool checkSuffix(string &s) {
    int idx = (int)origin.length() - 1;
    for (int i = (int)s.length() - 1; i >= 0; i--) {
        if (s[i] == 'W') break;
        if (s[i] != origin[idx--]) return false;
    }
    return true;
}

bool isExisted(string &str, int s, int t) {
    for (int i = 0; i + t - s <= origin.length(); i++) {
        bool isValid = true;
        for (int j = 0; j < t - s; j++) {
            if (origin[i + j] != str[s + j]) {
                isValid = false;
                break;
            }
        }
        if (isValid) return true;
    }
    return false;
}

bool checkSubstr(string &s) {
    int start = 0;
    for (int i = 0; i <= s.length(); i++) {
        if (s[i] == 'C' || s[i] == 'O' || s[i] == 'W' || s[i] == 0) {
            if (!isExisted(s, start, i)) return false;
            start = i + 1;
        }
    }
    return true;
}

int ELFhash(string &s) {
    int h = 0, x= 0;
    for (int i = 0; i < s.length(); i++) {
        h = (h << 4) + s[i];
        if ((x = h & 0xF0000000L) != 0) {
            h ^= (x >> 24);
        }
        h &= ~x;
    }
    return h;
}

bool dfs(string s, int depth) {
    if (depth == 0) {
        if (s == origin) return true;
        return false;
    }
    for (int O = 0; O < s.length(); O++) {
        if (s[O] != 'O') continue;
        for (int C = 0; C < O; C++) {
            if (s[C] != 'C') continue;
            for (int W = (int)s.length() - 1; W > O; W--) {
                if (s[W] != 'W') continue;
                string tmp = decryption(s, C, O, W);
                if (!checkPrefix(tmp) || !checkSuffix(tmp) || !checkSubstr(tmp)) continue;
                int h = ELFhash(tmp);
                if (m.find(h) != m.end()) continue;
                if (dfs(tmp, depth - 1)) return true;
                m.insert(h);
            }
        }
    }
    return false;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("cryptcow.in");
    ofstream fout ("cryptcow.out");
    string s;
    getline(fin, s);
    int len = (int)s.length();
    int T = (len - 47) / 3;
    if ((len - 47) % 3 == 0 && checkFrequency(s) && dfs(s, T)) fout << 1 << " " << T << endl;
    else fout << "0 0" << endl;
    return 0;
}
