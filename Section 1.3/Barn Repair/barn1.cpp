/*
 ID: cloudzf2
 PROG: barn1
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

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream fin ("barn1.in");
    ofstream fout ("barn1.out");
    int M, S, C;
    fin >> M >> S >> C;
    vector<int> stall(C, 0);
    for (int i = 0; i < C; i++) {
        fin >> stall[i];
    }
    sort(stall.begin(), stall.end());
    vector<int> empty;
    for (int i = 1; i < C; i++) {
        if (stall[i] - stall[i - 1] > 1) empty.push_back(stall[i] - stall[i - 1] - 1);
    }
    sort(empty.begin(), empty.end());
    int idx = (int)empty.size() - 1;
    int blocked = stall[stall.size() - 1] - stall[0] + 1;
    for (int i = 0; i < M - 1 && idx >= 0; i++) {
        blocked -= empty[idx--];
    }
    fout << blocked << endl;
    return 0;
}
