/*
 ID: cloudzf2
 PROG: skidesign
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

#define INT_MAX 2147483647
#define INT_MIN -2147483648

int main(int argc, const char * argv[]) {
    ifstream fin ("skidesign.in");
    ofstream fout ("skidesign.out");
    int N;
    fin >> N;
    vector<int> hill(N, 0);
    int minHeight = INT_MAX, maxHeight = INT_MIN;
    for (int i = 0; i < N; i++) {
        fin >> hill[i];
        minHeight = min(minHeight, hill[i]);
        maxHeight = max(maxHeight, hill[i]);
    }
    int ans = INT_MAX;
    for (int i = minHeight; i <= max(minHeight, maxHeight - 17); i++) {
        int count = 0;
        for (int j = 0; j < N; j++) {
            if (hill[j] < i) count += (i - hill[j]) * (i - hill[j]);
            else if (hill[j] > i + 17) count += (hill[j] - i - 17) * (hill[j] - i - 17);
        }
        ans = min(ans, count);
    }
    fout << ans << endl;
    return 0;
}
