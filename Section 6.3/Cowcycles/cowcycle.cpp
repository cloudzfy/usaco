/*
 ID: cloudzf2
 PROG: cowcycle
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

int F, R;
int F1, F2, R1, R2;
vector<int> f, r;
double minVar;
vector<int> ans1, ans2;

double getVariance(vector<double> &num) {
    double sum = 0;
    int N = (int)num.size();
    for (int i = 0; i < num.size(); i++) {
        sum += num[i];
    }
    double mean = sum / N;
    sum = 0;
    for (int i = 0; i < num.size(); i++) {
        sum += (num[i] - mean) * (num[i] - mean);
    }
    return sum / N;
}

void solve() {
    vector<double> quotient(F * R, 0);
    for (int i = 0; i < F; i++) {
        for (int j = 0; j < R; j++) {
            quotient[i * R + j] = (double)f[i] / r[j];
        }
    }
    sort(quotient.begin(), quotient.end());
    vector<double> diff(F * R - 1, 0);
    for (int i = 0; i < F * R - 1; i++) {
        diff[i] = quotient[i + 1] - quotient[i];
    }
    double var = getVariance(diff);
    if (var < minVar) {
        minVar = var;
        ans1 = f;
        ans2 = r;
    }
}

void dfs2(int n, int pos) {
    if (n == R) {
        if (f[0] * r[0] * 3 > f[F - 1] * r[R - 1]) return;
        solve();
        return;
    }
    for (int i = pos; i <= R2; i++) {
        r[n] = i;
        dfs2(n + 1, i + 1);
    }
}

void dfs1(int n, int pos) {
    if (n == F) {
        dfs2(0, R1);
        return;
    }
    for (int i = pos; i <= F2; i++) {
        f[n] = i;
        dfs1(n + 1, i + 1);
    }
}

int main(int argc, const char * argv[]) {
    ifstream fin ("cowcycle.in");
    ofstream fout ("cowcycle.out");
    fin >> F >> R;
    fin >> F1 >> F2 >> R1 >> R2;
    f.resize(F, 0);
    r.resize(R, 0);
    minVar = INF;
    dfs1(0, F1);
    for (int i = 0; i < F; i++) {
        if (i != 0) fout << " ";
        fout << ans1[i];
    }
    fout << endl;
    for (int i = 0; i < R; i++) {
        if (i != 0) fout << " ";
        fout << ans2[i];
    }
    fout << endl;
    return 0;
}
