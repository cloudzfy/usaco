/*
 ID: cloudzf2
 PROG: fence9
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

#define eps 1e-8
int main(int argc, const char * argv[]) {
    ifstream fin ("fence9.in");
    ofstream fout ("fence9.out");
    double n, m, p;
    fin >> n >> m >> p;
    int ans = 0;
    for (int i = 1; i < n; i++) {
        ans += floor(m / n * i - eps);
    }
    if (p >= n) {
        for (int i = 1; i <= p - n; i++) {
            if (i == p - n && n == 0) continue;
            ans += floor(m / (p - n) * i - eps);
        }
    } else {
        for (int i = 1; i < n - p; i++) {
            ans -= floor(m / (n - p) * i);
        }
    }
    fout << ans << endl;
    return 0;
}
