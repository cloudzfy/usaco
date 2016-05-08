/*
 ID: cloudzf2
 PROG: crypt1
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

bool isValid(int num, vector<bool> &m) {
    while (num) {
        if (!m[num % 10]) return false;
        num /= 10;
    }
    return true;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("crypt1.in");
    ofstream fout ("crypt1.out");
    int N;
    fin >> N;
    vector<int> digits(N, 0);
    vector<bool> m(10, false);
    for (int i = 0; i < N; i++) {
        fin >> digits[i];
        m[digits[i]] = true;
    }
    int count = 0;
    for (int a = 0; a < N; a++) {
        if (digits[a] == 0) continue;
        for (int b = 0; b < N; b++) {
            for (int c = 0; c < N; c++) {
                for (int d = 0; d < N; d++) {
                    if (digits[d] == 0) continue;
                    for (int e = 0; e < N; e++) {
                        int x = digits[a] * 100 + digits[b] * 10 + digits[c];
                        int y = digits[d] * 10 + digits[e];
                        if (digits[e] * x > 999 || digits[d] * x > 999) continue;
                        if (x * y > 9999) continue;
                        if (!isValid(digits[e] * x, m) || !isValid(digits[d] * x, m)) continue;
                        if (!isValid(x * y, m)) continue;
                        count++;
                    }
                }
            }
        }
    }
    fout << count << endl;
    return 0;
}
