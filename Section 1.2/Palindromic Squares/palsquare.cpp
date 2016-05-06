/*
 ID: cloudzf2
 PROG: palsquare
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
        char ch = N % B > 9 ? 'A' + N % B - 10 : '0' + N % B;
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
    ifstream fin ("palsquare.in");
    ofstream fout ("palsquare.out");
    int B;
    fin >> B;
    for (int N = 1; N <= 300; N++) {
        string sq = getNum(N * N, B);
        if (isPalindromic(sq)) {
            fout << getNum(N, B) << " " << sq << endl;
        }
    }
    return 0;
}
