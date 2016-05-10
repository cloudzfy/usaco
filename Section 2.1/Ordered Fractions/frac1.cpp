/*
 ID: cloudzf2
 PROG: frac1
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

struct fraction {
    int a, b;
    fraction(int a, int b) : a(a), b(b) {}
    bool operator<(const fraction &x) const {
        return a * x.b < x.a * b;
    }
};

int gcd(int a, int b) {
    while (a % b) {
        int r = a % b;
        a = b;
        b = r;
    }
    return b;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("frac1.in");
    ofstream fout ("frac1.out");
    int N;
    fin >> N;
    vector<fraction> data;
    data.push_back(fraction(0, 1));
    for (int i = 1; i <= N; i++) {
        for (int j = i; j <= N; j++) {
            if (gcd(i, j) != 1) continue;
            data.push_back(fraction(i, j));
        }
    }
    sort(data.begin(), data.end());
    for (int i = 0; i < data.size(); i++) {
        fout << data[i].a << "/" << data[i].b << endl;
    }
    return 0;
}
