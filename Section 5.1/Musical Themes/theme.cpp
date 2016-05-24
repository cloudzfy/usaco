/*
 ID: cloudzf2
 PROG: theme
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

int main(int argc, const char * argv[]) {
    ifstream fin ("theme.in");
    ofstream fout ("theme.out");
    int N;
    fin >> N;
    vector<int> data(N, 0);
    for (int i = 0; i < N; i++) {
        fin >> data[i];
    }
    int ans = 1;
    for (int i = N - 2; i > 0; i--) {
        int last = i;
        int tmp = 1;
        for (int j = 1; j <= i && last + j < N - 1; j++) {
            if (data[i - j] - data[i - j + 1] == data[N - 1 - j] - data[N - j]) {
                tmp++;
            } else {
                tmp = 1;
                last = i - j;
            }
            ans = max(ans, tmp);
        }
    }
    if (ans < 5) ans = 0;
    fout << ans << endl;
    return 0;
}
