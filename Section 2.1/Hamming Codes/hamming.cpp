/*
 ID: cloudzf2
 PROG: hamming
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

int hammingDis(int a, int b) {
    int c = a ^ b;
    int count = 0;
    while (c) {
        count += c & 1;
        c >>= 1;
    }
    return count;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("hamming.in");
    ofstream fout ("hamming.out");
    int N, B, D;
    fin >> N >> B >> D;
    int M = 1 << B;
    vector<int> ans;
    for (int i = 0; i < M; i++) {
        bool notAns = false;
        for (int j = 0; j < ans.size(); j++) {
            if (hammingDis(i, ans[j]) < D) {
                notAns = true;
                break;
            }
        }
        if (!notAns) {
            ans.push_back(i);
            if (ans.size() == N) break;
        }
    }
    for (int i = 0; i < ans.size(); i++) {
        if (i != 0) {
            if (i % 10 == 0) fout << endl;
            else fout << " ";
        }
        fout << ans[i];
    }
    fout << endl;
    return 0;
}
