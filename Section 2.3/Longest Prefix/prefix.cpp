/*
 ID: cloudzf2
 PROG: prefix
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
    ifstream fin ("prefix.in");
    ofstream fout ("prefix.out");
    vector<string> prefix;
    string p;
    while (true) {
        fin >> p;
        if (p == ".") break;
        prefix.push_back(p);
    }
    string str, s;
    while(fin >> s) {
        str += s;
    }
    int len = (int)str.length();
    vector<bool> dp(len + 1, false);
    dp[0] = true;
    for (int i = 0; i < len; i++) {
        if (dp[i]) {
            for (int j = 0; j < prefix.size(); j++) {
                bool isMatched = true;
                for (int k = 0; k < prefix[j].length(); k++) {
                    if (str[i + k] != prefix[j][k]) {
                        isMatched = false;
                        break;
                    }
                }
                if (isMatched) dp[i + (int)prefix[j].length()] = true;
            }
        }
    }
    for (int i = len; i >= 0; i--) {
        if (dp[i]) {
            fout << i << endl;
            return 0;
        }
    }
    return 0;
}
