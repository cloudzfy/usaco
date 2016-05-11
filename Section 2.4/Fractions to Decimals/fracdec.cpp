/*
 ID: cloudzf2
 PROG: fracdec
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

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream fin ("fracdec.in");
    ofstream fout ("fracdec.out");
    int N, D;
    fin >> N >> D;
    if (N % D == 0) {
        fout << N / D << ".0" << endl;
        return 0;
    }
    string ans = to_string(N / D) + ".";
    string decimal;
    vector<int> remainder(100000, -1);
    N %= D;
    int count = 0;
    while (true) {
        while (true) {
            if (remainder[N] >= 0) {
                ans += decimal.substr(0, remainder[N]) + "(" + decimal.substr(remainder[N]) + ")";
                for (int j = 0; j < ans.length(); j+=76) {
                    fout << ans.substr(j, 76) << endl;
                }
                return 0;
            }
            remainder[N] = count++;
            N *= 10;
            if (N >= D) break;
            decimal += "0";
        }
        decimal += to_string(N / D);
        N %= D;
        if (N == 0) {
            fout << ans + decimal << endl;
            return 0;
        }
    }
    
    return 0;
}
