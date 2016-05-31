/*
 ID: cloudzf2
 PROG: vans
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
#define MAXLEN 500

struct num {
    vector<int> value;
    num(vector<int> value) : value(value) {}
    num(int x) {
        value.resize(MAXLEN, 0);
        for (int i = 0; i < MAXLEN && x != 0; i++) {
            value[i] = x % 10;
            x /= 10;
        }
    }
    num operator+(const num &x) {
        vector<int> ret(MAXLEN, 0);
        int carry = 0;
        for (int i = 0; i < MAXLEN; i++) {
            ret[i] = value[i] + x.value[i] + carry;
            carry = ret[i] / 10;
            ret[i] %= 10;
        }
        return num(ret);
    }
    num operator-(const num &x) {
        vector<int> ret = value;
        for (int i = 0; i < MAXLEN; i++) {
            if (ret[i] < x.value[i]) {
                ret[i + 1]--;
                ret[i] += 10;
            }
            ret[i] -= x.value[i];
        }
        return num(ret);
    }
    num operator*(const int x) {
        vector<int> ret = value;
        int carry = 0;
        for (int i = 0; i < MAXLEN; i++) {
            ret[i] = ret[i] * x + carry;
            carry = ret[i] / 10;
            ret[i] %= 10;
        }
        return num(ret);
    }
};

int main(int argc, const char * argv[]) {
    ifstream fin ("vans.in");
    ofstream fout ("vans.out");
    int N;
    fin >> N;
    vector<num> f(1001, 0);
    vector<num> g(1001, 0);
    f[1] = num(2);
    f[2] = num(2);
    g[2] = num(2);
    f[3] = num(8);
    g[3] = num(4);
    for (int i = 4; i <= N; i++) {
        g[i] = f[i - 1] + g[i - 1];
        f[i] = g[i - 1] * 2 + f[i - 1] + f[i - 2] - f[i - 3];
    }
    int idx = MAXLEN - 1;
    while (idx > 0 && g[N].value[idx] == 0) idx--;
    while (idx >= 0) fout << g[N].value[idx--];
    fout << endl;
    return 0;
}
