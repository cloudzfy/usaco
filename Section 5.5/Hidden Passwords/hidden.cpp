/*
 ID: cloudzf2
 PROG: hidden
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

int main(int argc, const char * argv[]) {
    ifstream fin ("hidden.in");
    ofstream fout ("hidden.out");
    int N;
    fin >> N;
    string S, s;
    for (int i = 0; i < N; i += s.length()) {
        fin >> s;
        S += s;
    }
    S = S;
    int i = 0, j = 1;
    while (true) {
        if (i == j) j++;
        bool isValid = true;
        for (int k = 0; k < N; k++) {
            if (S[(i + k) % N] != S[(j + k) % N]) {
                isValid = false;
                if (S[(i + k) % N] > S[(j + k) % N]) {
                    i = i + k + 1;
                    break;
                } else {
                    j = j + k + 1;
                    break;
                }
            }
        }
        if (isValid) break;
    }
    fout << min(i, j) << endl;
    return 0;
}
