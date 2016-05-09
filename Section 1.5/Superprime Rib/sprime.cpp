/*
 ID: cloudzf2
 PROG: sprime
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

void listPrimes(vector<int> &primes) {
    vector<bool> isPrime(10001, true);
    for (int i = 2; i <= 10000; i++) {
        if (isPrime[i]) {
            for (int j = 2; i * j <= 10000; j++) {
                isPrime[i * j] = false;
            }
        }
    }
    for (int i = 2; i <= 10000; i++) {
        if (isPrime[i]) primes.push_back(i);
    }
}

int getNum(string s) {
    int num = 0;
    for (int i = 0; i < s.length(); i++) {
        num *= 10;
        num += s[i] - '0';
    }
    return num;
}

bool checkPrime(vector<int> primes, int num) {
    if (num < 2) return false;
    for (int i = 0; i < primes.size() && primes[i] * primes[i] <= num; i++) {
        if (num % primes[i] == 0) return false;
    }
    return true;
}
int main(int argc, const char * argv[]) {
    ifstream fin ("sprime.in");
    ofstream fout ("sprime.out");
    int N;
    fin >> N;
    vector<int> primes;
    listPrimes(primes);
    vector<string> ans;
    ans.push_back("");
    int idx = 0;
    while (ans[idx].length() < N && idx < ans.size()) {
        for (int i = 1; i <= 9; i++) {
            char ch = '0' + i;
            string tmp = ans[idx] + ch;
            if (checkPrime(primes, getNum(tmp))) ans.push_back(tmp);
        }
        idx++;
    }
    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) {
        if (ans[i].length() == N) fout << ans[i] << endl;
    }
    return 0;
}
