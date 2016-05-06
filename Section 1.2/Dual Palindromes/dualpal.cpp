/*
 ID: cloudzf2
 PROG: dualpal
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

string getNum(int N, int B) {
    string num;
    while (N) {
        char ch = '0' + N % B;
        num = ch + num;
        N /= B;
    }
    return num;
}

bool isPalindromic(string s) {
    int left = 0, right = (int)s.length() - 1;
    while (left < right) {
        if (s[left++] != s[right--]) return false;
    }
    return true;
}
int main(int argc, const char * argv[]) {
    ifstream fin ("dualpal.in");
    ofstream fout ("dualpal.out");
    int N, S;
    fin >> N >> S;
    S++;
    while (N--) {
        int count = 0;
        while (count < 2) {
            count = 0;
            for (int B = 2; B <= 10; B++) {
                if (isPalindromic(getNum(S, B))) count++;
            }
            S++;
        }
        fout << S - 1 << endl;
    }
    return 0;
}
