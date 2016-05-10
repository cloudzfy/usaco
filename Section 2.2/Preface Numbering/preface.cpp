/*
 ID: cloudzf2
 PROG: preface
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

void count(unordered_map<char, int> &m, string s) {
    for (int i = 0; i < s.length(); i++) {
        m[s[i]]++;
    }
}

int main(int argc, const char * argv[]) {
    ifstream fin ("preface.in");
    ofstream fout ("preface.out");
    string ones[9] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    string tens[9] = {"X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    string hundreds[9] = {"C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    string thousands[3] = {"M", "MM", "MMM"};
    int N;
    fin >> N;
    unordered_map<char, int> m;
    for (int i = 1; i <= N; i++) {
        int num = i;
        if (num / 1000 > 0) {
            count(m, thousands[num / 1000 - 1]);
            num %= 1000;
        }
        if (num / 100 > 0) {
            count(m, hundreds[num / 100 - 1]);
            num %= 100;
        }
        if (num / 10 > 0) {
            count(m, tens[num / 10 - 1]);
            num %= 10;
        }
        if (num > 0) {
            count(m, ones[num - 1]);
        }
    }
    if (m.find('I') != m.end()) fout << "I " << m['I'] << endl;
    if (m.find('V') != m.end()) fout << "V " << m['V'] << endl;
    if (m.find('X') != m.end()) fout << "X " << m['X'] << endl;
    if (m.find('L') != m.end()) fout << "L " << m['L'] << endl;
    if (m.find('C') != m.end()) fout << "C " << m['C'] << endl;
    if (m.find('D') != m.end()) fout << "D " << m['D'] << endl;
    if (m.find('M') != m.end()) fout << "M " << m['M'] << endl;
    return 0;
}
