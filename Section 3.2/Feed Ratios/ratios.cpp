/*
 ID: cloudzf2
 PROG: ratios
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

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream fin ("ratios.in");
    ofstream fout ("ratios.out");
    vector<vector<int> > maps(4, vector<int>(3, 0));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            fin >> maps[i][j];
        }
    }
    int target = maps[0][0] + maps[0][1] + maps[0][2];
    vector<int> ans(4, 0);
    int sum = -1;
    for (int i = 0; i <= 100; i++) {
        for (int j = 0; j <= 100; j++) {
            for (int k = 0; k <= 100; k++) {
                if (i + j + k == 0) continue;
                int a = maps[1][0] * i + maps[2][0] * j + maps[3][0] * k;
                int b = maps[1][1] * i + maps[2][1] * j + maps[3][1] * k;
                int c = maps[1][2] * i + maps[2][2] * j + maps[3][2] * k;
                if ((a + b + c) % target != 0) continue;
                int m = (a + b + c) / target;
                if (a == m * maps[0][0] && b == m * maps[0][1] && c == m * maps[0][2]) {
                    if (sum == -1 || i + j + k < sum) {
                        ans[0] = i;
                        ans[1] = j;
                        ans[2] = k;
                        ans[3] = m;
                        sum = i + j + k;
                    }
                }
                
            }
        }
    }
    if (sum == -1) fout << "NONE" << endl;
    else fout << ans[0] << " " << ans[1] << " " << ans[2] << " " << ans[3] << endl;
    return 0;
}
