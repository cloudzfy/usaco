/*
 ID: cloudzf2
 PROG: combo
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

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream fin ("combo.in");
    ofstream fout ("combo.out");
    int N;
    fin >> N;
    vector<int> a(3, 0);
    vector<int> b(3, 0);
    for (int i = 0; i < 3; i++) {
        fin >> a[i];
    }
    for (int i = 0; i < 3; i++) {
        fin >> b[i];
    }
    int ans = 1;
    for (int i = 0; i < 3; i++) {
        if (a[i] == b[i]) ans *= min(N, 5);
        else if (a[i] < b[i]) {
            if (b[i] - a[i] <= 4 && a[i] + N - b[i] <= 4) ans *= N;
            else if (b[i] - a[i] <= 4) ans *= 5 - (b[i] - a[i]);
            else if (a[i] + N - b[i] <= 4) ans *= 5 - (a[i] + N - b[i]);
            else ans *= 0;
        } else {
            if (a[i] - b[i] <= 4 && b[i] + N - a[i] <= 4) ans *= N;
            else if (a[i] - b[i] <= 4) ans *= 5 - (a[i] - b[i]);
            else if (b[i] + N - a[i] <= 4) ans *= 5 - (b[i] + N - a[i]);
            else ans *= 0;
        }
    }
    int x = min(N, 5);
    fout << x * x * x * 2 - ans << endl;
    return 0;
}
