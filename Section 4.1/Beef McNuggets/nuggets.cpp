/*
 ID: cloudzf2
 PROG: nuggets
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

int gcd(int a, int b) {
    while (b) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

int main(int argc, const char * argv[]) {
    ifstream fin ("nuggets.in");
    ofstream fout ("nuggets.out");
    int N;
    fin >> N;
    vector<int> nu(N, 0);
    for (int i = 0; i < N; i++) {
        fin >> nu[i];
    }
    sort(nu.begin(), nu.end());
    int val = nu[0];
    for (int i = 1; i < N; i++) {
        val = gcd(val, nu[i]);
    }
    if (val != 1) {
        fout << 0 << endl;
        return 0;
    }
    int M = lcm(nu[N - 1], nu[N - 2]);
    vector<bool> dp(M + 1, false);
    dp[0] = true;
    for (int i = 0; i < N; i++) {
        for (int j = nu[i]; j <= M; j++) {
            if (dp[j - nu[i]]) dp[j] = true;
        }
    }
    for (int i = M; i >= 0; i--) {
        if (!dp[i]) {
            fout << i << endl;
            return 0;
        }
    }
    fout << 0 << endl;
    return 0;
}
