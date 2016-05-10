/*
 ID: cloudzf2
 PROG: sort3
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

int main(int argc, const char * argv[]) {
    ifstream fin ("sort3.in");
    ofstream fout ("sort3.out");
    int N;
    fin >> N;
    vector<int> a(N, 0);
    vector<int> count(3, 0);
    for (int i = 0; i < N; i++) {
        fin >> a[i];
        count[a[i] - 1]++;
    }
    vector<vector<int> > map(3, vector<int>(3, 0));
    for (int i = 0; i < N; i++) {
        if (i < count[0]) {
            map[0][a[i] - 1]++;
        } else if (i < count[0] + count[1]) {
            map[1][a[i] - 1]++;
        } else {
            map[2][a[i] - 1]++;
        }
    }
    int ans = 0;
    int diff = min(map[0][1], map[1][0]);
    ans += diff;
    map[0][1] -= diff;
    map[1][0] -= diff;
    diff = min(map[0][2], map[2][0]);
    ans += diff;
    map[0][2] -= diff;
    map[2][0] -= diff;
    diff = min(map[1][2], map[2][1]);
    ans += diff;
    map[1][2] -= diff;
    map[2][1] -= diff;
    diff = map[0][1] + map[1][0] + map[0][2] + map[2][0] + map[1][2] + map[2][1];
    ans += diff / 3 * 2;
    fout << ans << endl;
    return 0;
}
