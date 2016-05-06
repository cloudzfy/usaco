/*
 ID: cloudzf2
 PROG: beads
 LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cstring>
#include <vector>

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream fin ("beads.in");
    ofstream fout ("beads.out");
    int N;
    string s;
    fin >> N >> s;
    bool isRed = s[0] != 'b';
    bool allSame = true;
    for (int i = 0; i < N; i++) {
        if ((isRed && s[i] == 'b') || (!isRed && s[i] == 'r')) {
            allSame = false;
            break;
        }
    }
    if (allSame) {
        fout << N << endl;
        return 0;
    }
    s = s + s;
    int r = 0, b = 0, w = 0;
    int ans = 0;
    for (int i = 0; i < s.length(); i++) {
        if (isRed) {
            if (s[i] == 'b') {
                ans = max(ans, r + b + w);
                b = w + 1;
                w = 0;
                isRed = false;
            } else if (s[i] == 'w') {
                w++;
            } else {
                r += w + 1;
                w = 0;
            }
        } else {
            if (s[i] == 'r') {
                ans = max(ans, r + b + w);
                r = w + 1;
                w = 0;
                isRed = true;
            } else if (s[i] == 'w') {
                w++;
            } else {
                b += w + 1;
                w = 0;
            }
        }
    }
    fout << min(ans, N) << endl;
    return 0;
}
