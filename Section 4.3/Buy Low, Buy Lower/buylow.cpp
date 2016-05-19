/*
 ID: cloudzf2
 PROG: buylow
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

struct node {
    int value;
    int length;
    int count[100];
    node(int value) : value(value), length(1) {
        memset(count, 0, sizeof(count));
    }
};

void add(int a[100], int b[100]) {
    int carry = 0;
    for (int i = 0; i < 100; i++) {
        a[i] += b[i] + carry;
        carry = a[i] / 10;
        a[i] %= 10;
    }
}

int main(int argc, const char * argv[]) {
    ifstream fin ("buylow.in");
    ofstream fout ("buylow.out");
    int N, val;
    fin >> N;
    vector<node> dp;
    for (int i = 0; i < N; i++) {
        fin >> val;
        dp.push_back(node(val));
    }
    unordered_set<int> m;
    int ans = 0;
    for (int i = 0; i < N; i++) {
        int len = 0;
        for (int j = i - 1; j >= 0; j--) {
            if (dp[j].value > dp[i].value) {
                len = max(len, dp[j].length);
            }
        }
        ans = max(ans, len + 1);
        dp[i].length = len + 1;
        if (len == 0) {
            dp[i].count[0] = 1;
        } else {
            for (int j = i - 1; j >= 0; j--) {
                if (dp[j].value > dp[i].value && dp[j].length == len && m.find(dp[j].value) == m.end()) {
                    m.insert(dp[j].value);
                    add(dp[i].count, dp[j].count);
                }
            }
        }
        m.clear();
    }
    fout << ans << " ";
    int c[100];
    memset(c, 0, sizeof(c));
    for (int i = N - 1; i >= 0; i--) {
        if (dp[i].length == ans && m.find(dp[i].value) == m.end()) {
            add(c, dp[i].count);
            m.insert(dp[i].value);
        }
    }
    int idx = 99;
    while (idx > 0 && c[idx] == 0) idx--;
    while (idx >= 0) {
        fout << c[idx];
        idx--;
    }
    fout << endl;
    return 0;
}
