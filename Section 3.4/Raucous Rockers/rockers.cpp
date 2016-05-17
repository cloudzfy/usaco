/*
 ID: cloudzf2
 PROG: rockers
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

int main(int argc, const char * argv[]) {
    ifstream fin ("rockers.in");
    ofstream fout ("rockers.out");
    int N, T, M;
    fin >> N >> T >> M;
    vector<int> songs(N, 0);
    for (int i = 0; i < N; i++) {
        fin >> songs[i];
    }
    int NN = 1 << N;
    int ans = 0;
    for (int i = 0; i < NN; i++) {
        int count = 0;
        int disk = 0;
        int disks = 0;
        bool isValid = true;
        for (int j = 0; j < N; j++) {
            if ((1 << j) & i) {
                count++;
                if (songs[j] > T) {
                    isValid = false;
                    break;
                }
                if (disk + songs[j] <= T) {
                    disk += songs[j];
                } else {
                    disks++;
                    disk = songs[j];
                }
            }
        }
        if (disk > 0) disks++;
        if (isValid && disks <= M) ans = max(ans, count);
    }
    fout << ans << endl;
    return 0;
}
